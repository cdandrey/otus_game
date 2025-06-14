#pragma once


#include <mutex>
#include <thread>
#include <atomic>
#include <concurrent_queue.h>

#include "AbstractCommand.h"

namespace otg {

class CommandWorker
{
public:
    CommandWorker();
    ~CommandWorker();

    void run();
    void push(const AbstractCommandPtr& cmd);
    void start();
    void stop();
    void interrupt();
    bool isRunning() const;

private:
    std::atomic_bool m_interrupt{ false };
    std::atomic_bool m_cancel{ false };
    std::atomic_bool m_thread_is_run{ false };
    Concurrency::concurrent_queue<AbstractCommandPtr> m_commands;
    std::unique_ptr<std::thread> m_thread;
};

}  // namespace otg