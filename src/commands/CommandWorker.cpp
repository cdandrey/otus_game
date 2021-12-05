#include "CommandWorker.h"

namespace otg {

CommandWorker::CommandWorker()
    : m_cancel {false}
    , m_thread {std::make_unique<std::thread>(&CommandWorker::run, this)}
{
}

CommandWorker::~CommandWorker()
{
	stop();
	try {
		if (m_thread->joinable()) {
			m_thread->join();
		}
	} catch (std::system_error &) {
		// Can't stop thread of CommandWorker
	}
}

void CommandWorker::push(const AbstractCommandPtr &cmd)
{
	std::unique_lock<std::mutex> g {m_mutex};
	if (!m_cancel) {
		m_commands.push(cmd);
		m_cv.notify_one();
	}
}

void CommandWorker::stop()
{
	std::unique_lock<std::mutex> g {m_mutex};
	m_cancel = true;
	m_cv.notify_all();
}

void CommandWorker::interrupt()
{
	std::unique_lock<std::mutex> g {m_mutex};
	m_cancel = true;
	while (!m_commands.empty()) {
		m_commands.pop();
	}
	m_cv.notify_all();
}

void CommandWorker::run()
{
	while (!m_cancel || !m_commands.empty()) {
		std::unique_lock<std::mutex> g {m_mutex};
		m_cv.wait(g, [this]() {
			return m_cancel || !m_commands.empty();
		});

		if (m_cancel && m_commands.empty()) {
			break;
		}

		AbstractCommandPtr cmd;
		std::swap(cmd, m_commands.front());
		m_commands.pop();
		g.unlock();

		const auto onError = [this](const ExceptionError &error) {
			switch (error.type()) {
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

		cmd->execute().map_error(onError);
	}
}

}  // namespace otg