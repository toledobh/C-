#ifndef threadManager_h
#define threadManager_h

#include <iostream>  
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadControlBlock {
public:
    unique_ptr<thread> thread;
    ThreadControlBlock() = default;
};

class ThreadManager {
private:
    vector<ThreadControlBlock> threadBlocks;
    mutex mtx;
    condition_variable cv;
    bool isTerminated;

public:
    ThreadManager();

    void createThread(vector<string>& truck);

    void terminateThreads();

    void startScheduler();
};

#endif