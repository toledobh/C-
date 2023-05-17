#include <iostream>

// Abstract class for Thread Manager
class ThreadManagerAbstract {
public:
    virtual void createThread() = 0; // Create a new thread
    virtual void terminateThread() = 0; // Terminate a thread
    virtual void scheduleThread() = 0; // Schedule the execution of threads
    virtual void synchronizeThreads() = 0; // Synchronize the execution of threads

    virtual ~ThreadManagerAbstract() {} // Virtual destructor
};
