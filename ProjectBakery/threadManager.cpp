#include "threadManager.h"

ThreadManager::ThreadManager() {
    isTerminated = false;
}

void ThreadManager::createThread(vector<string>& truck) {
    unique_lock<mutex> lock(mtx);

    // Create a new thread and add it to the thread blocks
    threadBlocks.emplace_back();

    threadBlocks.back().thread = make_unique<thread>([this, index = threadBlocks.size() - 1, &truck]() {
        // Thread execution logic goes here
        while (!isTerminated) {
            // Check if there are any products left to store
            string product;
            {
                lock_guard<mutex> guard(mtx);
                if (!truck.empty()) {
                    // Retrieve the next product from the truck
                    product = truck.front();
                    truck.erase(truck.begin());
                }
            }

            // Store the product if available
            if (!product.empty()) {

                // Perform the storing task
                    chrono::steady_clock::time_point start = chrono::steady_clock::now(); // Start measuring time
                    {
                        lock_guard<mutex> coutLock(mtx); // Lock cout
                        chrono::steady_clock::time_point end = chrono::steady_clock::now(); // Stop measuring time
                        cout << "Thread " << char('A' + index) << " is competing for the lock.\n";
                        cout << "Thread " << char('A' + index) << " acquired the lock in "
                                    << chrono::duration_cast<chrono::nanoseconds >(end - start).count()
                                    << " nanoseconds.\n";
                        cout << "Thread " << char('A' + index) << " is Storing " << product << " in the storage.\n\n";
                    }

                    cout << "\nThread " << char('A' + index) << " released the lock.\n\n\n";

                    // Simulate the time taken to store the productcoutLock
                    this_thread::sleep_for(chrono::seconds(6));

            } else {
                // If there are no more products, exit the thread
                {
                    lock_guard<mutex> coutLock(mtx); // Lock cout
                    cout << "\nThread " << char('A' + index) << ": No more products to store. Exiting.";
                }
                break;
            }
        }
        // terminateThreads();
    });
    cv.notify_one();
}

void ThreadManager::terminateThreads() {
    unique_lock<mutex> lock(mtx);

    // Set the termination flag to true
    isTerminated = true;

    // Notify all threads to terminate
    cv.notify_all();
}

void ThreadManager::startScheduler() {
    unique_lock<mutex> lock(mtx);

    // Start scheduling the threads from the thread blocks
    while (!isTerminated) {
        // Wait until a thread is available in the thread blocks
        while (threadBlocks.empty() && !isTerminated) {
            cv.wait(lock);
        }

        // Retrieve the next thread to run from the thread blocks
        if (!threadBlocks.empty()) {
            ThreadControlBlock tcb = move(threadBlocks.back());
            threadBlocks.pop_back();
            lock.unlock();

            // Resume execution of the selected thread
            tcb.thread->join();

            lock.lock();
        }
    }
}
