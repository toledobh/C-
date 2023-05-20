#include "processScheduler.h"

int ProcessScheduler::getTimeSlice(){
    return timeSlice;
}

void ProcessScheduler::addProcess(Process& process) {
    // Add the new process into the queue.
    readyQueue.push(process);

    // Show a message of the new process.
    cout << "Process-Id: " << process.getProcessId() << " (" << process.getProcessName() << ") "
            << "created. Its burst time is " << process.getBurstTime() << "." << endl;
}

void ProcessScheduler::terminateProcess(Process removeProcess) {
    if (!readyQueue.empty()) {
        // Permanently remove the current process from the queue
        readyQueue.pop();

        // Show a message of the removed process.
        cout << "Process " << removeProcess.getProcessId()   << " ("<<removeProcess.getProcessName()<<") " << "completed.\n" << endl;
    }
}

void ProcessScheduler::contextSwitch(Process oldProcess) {
    if (!readyQueue.empty()) {
        // Temporarily remove the current process from the queue
        readyQueue.pop();

        // Add oldProcess at the end of the queue
        readyQueue.push(oldProcess);

        // Retrieve the new current process.
        Process newProcess = readyQueue.front();

        // Show a message of the context switching from the oldProcess to the newProcess
        cout << "Switching to Process " << newProcess.getProcessId() << "\n" << endl;
    }
}

void ProcessScheduler::runScheduler() {
    while (!readyQueue.empty()) {
        // Sleep process according to the time slice interval.
        Process currentProcess = readyQueue.front();
        cout << "Process " << currentProcess.getProcessId() << " working..." << endl;
        sleep(timeSlice);

        // Deduct the time slice from the burst time of the current process.
        currentProcess.deductTimeSlice(timeSlice);

        //Evaluate if the burst time reached zero
        if (currentProcess.isCompleted()) {
            // Terminate the process whose burst time is zero
            terminateProcess(currentProcess);
        }
        else{
            // Select the next process to run
            cout << "Saving state of Process " << currentProcess.getProcessId() << " remaining time " << currentProcess.getRemainingTime() << endl;
            contextSwitch(currentProcess);
        }
    }
}
