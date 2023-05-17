#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

struct ThreadControlBlock {
    thread threadObj;
    bool terminated;
};

class ThreadManager {
private:
    queue<ThreadControlBlock*> threadQueue;
    mutex queueMutex;
    condition_variable queueCondition;
    bool isRunning;

public:
    ThreadManager() : isRunning(true) {}

    void createThread() {
        unique_lock<mutex> lock(queueMutex);
        ThreadControlBlock* tcb = new ThreadControlBlock();
        tcb->terminated = false;
        tcb->threadObj = thread(&ThreadManager::runThread, this, tcb);
        threadQueue.push(tcb);
        lock.unlock();
        queueCondition.notify_one();
    }

    void terminateThread() {
        unique_lock<mutex> lock(queueMutex);
        if (!threadQueue.empty()) {
            ThreadControlBlock* tcb = threadQueue.front();
            tcb->terminated = true;
            tcb->threadObj.join();
            delete tcb;
            threadQueue.pop();
        }
    }

    void runThread(ThreadControlBlock* tcb) {
        while (isRunning && !tcb->terminated) {
            // Thread execution logic goes here...
            // You can add code for synchronization primitives such as locks and semaphores.
        }
    }

    void stopManager() {
        isRunning = false;
        queueCondition.notify_all();
    }
};

int main() {
    ThreadManager manager;
    manager.createThread();
    manager.createThread();
    manager.createThread();

    // Sleep for a while to allow threads to execute
    this_thread::sleep_for(chrono::milliseconds(1000));

    manager.terminateThread();
    manager.terminateThread();
    manager.terminateThread();

    manager.stopManager();
    return 0;
}
