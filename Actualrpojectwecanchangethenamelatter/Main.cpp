#include <iostream>
#include "ThreadManager.cpp"

int main() {
    ThreadManager threadManager;

    threadManager.createThread();
    threadManager.scheduleThread();
    threadManager.synchronizeThreads();
    threadManager.terminateThread();

    return 0;
}