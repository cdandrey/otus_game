#pragma once

#include "AbstractCommand.h"

#include <mutex>
#include <thread>
#include <atomic>
#include <concurrent_queue.h>

namespace otg {

class CommandWorker
{
public:
    CommandWorker();
    ~CommandWorker();

    void run();
    void push(const AbstractCommandPtr& cmd);
    void stop();
    void interrupt();
    bool isRunning() const;

private:
    std::atomic_bool m_interrupt{ false };
    std::atomic_bool m_cancel{ false };
    Concurrency::concurrent_queue<AbstractCommandPtr> m_commands;
    std::unique_ptr<std::thread> m_thread;
};

}  // namespace otg