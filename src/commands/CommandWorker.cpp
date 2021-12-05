#include "CommandWorker.h"

#include <iostream>

namespace otg {

CommandWorker::CommandWorker()
{
    std::cout << "Constract" << std::endl;
}

CommandWorker::~CommandWorker()
{
    stop();
    try
    {
        if (m_thread->joinable())
        {
            std::cout << "Destructor: join" << std::endl;
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
    std::cout << "Push" << std::endl;
    m_commands.push(cmd);
}

void CommandWorker::start()
{
    bool running{ false };
    if (m_running.compare_exchange_strong(running, true, std::memory_order_release, std::memory_order_relaxed))
    {
        m_thread = std::make_unique<std::thread>(&CommandWorker::run, this);
    }
}

void CommandWorker::stop()
{
    m_cancel.store(true, std::memory_order_release);
    std::cout << "Stop" << std::endl;
}

void CommandWorker::interrupt()
{
    m_interrupt.store(true, std::memory_order_release);
    std::cout << "Interrupt" << std::endl;
}

bool CommandWorker::isRunning() const
{
    return !m_interrupt.load(std::memory_order_acquire) &&  //
        (!m_cancel.load(std::memory_order_acquire) || !m_commands.empty());
}

void CommandWorker::run()
{
    std::cout << "Run..." << std::endl;
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
        std::cout << "Running..." << std::endl;
        if (m_commands.try_pop(cmd))
        {
            std::cout << "Execute..." << std::endl;
            cmd->execute().map_error(onError);
        }
    }
    m_running.store(false, std::memory_order_release);
    std::cout << "Exit run..." << std::endl;
}

}  // namespace otg