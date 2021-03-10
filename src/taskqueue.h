#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <vector>
#include <atomic>
#include <thread>
#include <functional>
#include <condition_variable>

class Task_Queue final
{
public:
    explicit Task_Queue(const Task_Queue&) = delete;
    Task_Queue& operator=(const Task_Queue&) = delete;

    explicit Task_Queue();
    ~Task_Queue() noexcept ;

    void add(const std::function<void ()>& task);

private:
    std::atomic<bool> m_isStop {false};
    std::thread m_thread;
    std::condition_variable m_cv;

    mutable std::mutex m_mutex;
    std::vector<std::function<void ()>> m_tasks;
};


#endif // TASKQUEUE_H
