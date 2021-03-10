#include "taskqueue.h"

#include <iostream>

Task_Queue::Task_Queue() :
    m_thread([this](){
    while(!m_isStop) {
        std::unique_lock<std::mutex> lock(m_mutex);

        if (m_isStop)
            break;

        m_cv.wait(lock, [this](){
            return 0 < m_tasks.size() || m_isStop;
        });

        std::vector<std::function<void ()>> tasks;
        tasks.swap(m_tasks);
        lock.unlock();

        for(const auto &task : tasks)
            task();
    }})
{
}

Task_Queue::~Task_Queue() noexcept
{
    m_isStop = true;
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.notify_all();
    m_thread.join();
}

void Task_Queue::add(const std::function<void ()>& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_tasks.push_back(task);
    m_cv.notify_one();
}
