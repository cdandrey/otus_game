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
	std::queue<AbstractCommandPtr> m_commands;
	std::mutex m_mutex;
	std::unique_ptr<std::thread> m_thread;
	std::condition_variable m_cv;
	bool m_cancel;
};

}  // namespace otg