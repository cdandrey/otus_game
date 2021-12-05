#pragma once

#include "AbstractCommand.h"

#include <mutex>
#include <queue>
#include <thread>

namespace otg {

class CommandWorker
{
public:
	CommandWorker();
	~CommandWorker();

	void run();
	void push(const AbstractCommandPtr &cmd);
	void stop();
	void interrupt();

private:
	bool m_cancel;
	std::queue<AbstractCommandPtr> m_commands;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::unique_ptr<std::thread> m_thread;
};

}  // namespace otg