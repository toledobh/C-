#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

// Thread Control Block (TCB) data structure
struct Thread {
    int id;
    thread t;
};

class ThreadManager {
private:
    queue<Thread> readyQueue;
    mutex mtx;
    condition_variable cv;
    bool isTerminated;

public:
    ThreadManager() : isTerminated(false) {}

    void createThread(int id) {
        unique_lock<mutex> lock(mtx);
        readyQueue.push({id, thread(&ThreadManager::runThread, this, id)});
        cv.notify_all();
    }

    void terminateThread(int id) {
        unique_lock<mutex> lock(mtx);
        isTerminated = true;
        cv.notify_all();
    }

    void runThread(int id) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            // Check if the thread needs to be terminated
            if (isTerminated) {
                isTerminated = false;
                break;
            }

            // Check if the thread is at the front of the ready queue
            if (!readyQueue.empty() && readyQueue.front().id == id) {
                Thread currentThread = readyQueue.front();
                readyQueue.pop();

                // Simulate thread execution
                cout << "Thread " << currentThread.id << " is running." << endl;
                lock.unlock();
                this_thread::sleep_for(chrono::seconds(1));  // Simulate work
                lock.lock();

                // Check if the thread is still valid
                if (currentThread.t.joinable())
                    currentThread.t.detach();
            } else {
                cv.wait(lock);  // Wait until the thread is at the front of the ready queue
            }
        }
    }
};

int main() {
    ThreadManager manager;

    // Create threads
    manager.createThread(1);
    manager.createThread(2);
    manager.createThread(3);

    // Simulate work
    this_thread::sleep_for(chrono::seconds(5));

    // Terminate threads
    manager.terminateThread(1);
    manager.terminateThread(2);
    manager.terminateThread(3);

    return 0;
}
