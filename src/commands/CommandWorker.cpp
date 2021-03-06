#include "CommandWorker.h"

namespace otg {

CommandWorker::CommandWorker()
{
}

CommandWorker::~CommandWorker()
{
    stop();
    try
    {
        if (m_thread->joinable())
        {
            m_thread->join();
        }
    }
    catch (std::system_error&)
    {
        // Can't stop thread of CommandWorker
    }
}

void CommandWorker::push(const AbstractCommandPtr& cmd)
{
    if (m_interrupt.load(std::memory_order_acquire) || m_cancel.load(std::memory_order_acquire))
    {
        return;
    }
    m_commands.push(cmd);
}

void CommandWorker::start()
{
    bool expected{ false };
    if (m_thread_is_run.compare_exchange_strong(expected, true, std::memory_order_acq_rel))
    {
        m_thread = std::make_unique<std::thread>(&CommandWorker::run, this);
    }
}

void CommandWorker::stop()
{
    m_cancel.store(true, std::memory_order_release);
}

void CommandWorker::interrupt()
{
    m_interrupt.store(true, std::memory_order_release);
}

bool CommandWorker::isRunning() const
{
    return !m_interrupt.load(std::memory_order_acquire) &&  //
        (!m_cancel.load(std::memory_order_acquire) || !m_commands.empty());
}

void CommandWorker::run()
{
    const auto onError = [this](const ExceptionError& error) {
        switch (error.type())
        {
        case ExceptionErrorType::ExecuteStop:
            stop();
            break;

        case ExceptionErrorType::ExecuteInterrupt:
            interrupt();
            break;

        default:
            break;
        }
    };

    AbstractCommandPtr cmd;

    while (isRunning())
    {
        if (m_commands.try_pop(cmd))
        {
            cmd->execute().map_error(onError);
        }
    }
    m_thread_is_run.store(true, std::memory_order_release);
}

}  // namespace otg