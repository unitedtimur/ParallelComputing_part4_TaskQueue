#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>

#include "taskqueue.h"
#include "threadsafeprint.h"

int main()
{
    std::cout << "Available threads: " << std::thread::hardware_concurrency() << std::endl;

    Task_Queue taskQueue;

    std::atomic<bool> canEnd = false;

    taskQueue.add([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        sPrint << "First task" << std::endl;
    });

    taskQueue.add([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        sPrint << "Second task" << std::endl;
    });

    taskQueue.add([&](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        sPrint << "Third task" << std::endl;
        canEnd = true;
    });

    while (!canEnd) {};

    return 0;
}

