#ifndef processScheduler_h
#define processScheduler_h

#include <iostream>
#include <queue>
#include <unistd.h>
#include "process.h"

class ProcessScheduler {
private:
    queue<Process> readyQueue;  // Ready queue to hold processes
    const int timeSlice = 4;    // Time slice for round-robin scheduling

public:

    /**
     * Add a process into the queue
     *
     * @param process represents the process to add in the queue.
     * @return It does not return any value.
     */
    void addProcess(Process& process);

    /**
     * Terminate the currently running process.
     *
     * @param removeProcess represents the process to remove from the queue.
     * @return It does not return any value.
     */
    void terminateProcess(Process removeProcess);

    /**
     * Perform context switching. 
     * 
     * Relocate the current process to the end of the queue
     *
     * @param oldProcess represents the current process in the queue.
     * @return It does not return any value.
     */    
    void contextSwitch(Process oldProcess);

    /**
     *  Round Robin Scheduling (RRS)
     * 
     *  Loop through all items in the queue to implement RRS
     *
     * @return It does not return any value.
     */    
    void runScheduler();

    int getTimeSlice();
};

#endif
