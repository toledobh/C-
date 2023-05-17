#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

struct ThreadControlBlock {}

class ThreadManager {
    queue<ThreadControlBlock*> threadQueue;
    mutex queueMutex;

    void createThread() {}
    void terminateThread() {}
    void runScheduler() {}
}

