#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

// Thread Control Block (TCB) data structure
struct ThreadControlBlock {
    std::unique_ptr<std::thread> thread;
    bool terminated;
};

// Thread Manager class
class ThreadManager {
public:
    ThreadManager() : terminated(false) {}

    // System call interface to create a new thread
    void createThread() {
        std::unique_lock<std::mutex> lock(mutex_);
        threads_.push(ThreadControlBlock{ std::make_unique<std::thread>(&ThreadManager::executeThread, this), false });
        condition_.notify_one();
    }

    // System call interface to terminate the currently running thread
    void terminateCurrentThread() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!threads_.empty()) {
            threads_.front().terminated = true;
            threads_.front().thread->join();
            threads_.pop();
        }
    }

    // Simple thread scheduler
    void executeThread() {
        while (!terminated) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (threads_.empty()) {
                condition_.wait(lock);
            }
            if (!threads_.empty()) {
                ThreadControlBlock tcb = std::move(threads_.front());
                lock.unlock();
                tcb.thread->join();
                lock.lock();
                if (!tcb.terminated) {
                    threads_.push(std::move(tcb));
                }
                threads_.pop();
            }
        }
    }

private:
    std::queue<ThreadControlBlock> threads_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool terminated;
};

// Example usage
int main() {
    ThreadManager threadManager;
    threadManager.createThread();
    threadManager.createThread();
    threadManager.createThread();

    // Simulate execution
    std::this_thread::sleep_for(std::chrono::seconds(2));

    threadManager.terminateCurrentThread();
    threadManager.terminateCurrentThread();
    threadManager.terminateCurrentThread();

    return 0;
}
