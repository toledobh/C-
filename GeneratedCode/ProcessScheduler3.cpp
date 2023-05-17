#include <iostream>
#include <queue>

using namespace std;

// Process Control Block (PCB) structure
struct PCB {
    int pid;
    int burstTime;
    int remainingTime;
};

// Ready queue to hold processes
queue<PCB> readyQueue;

// Time slice for round-robin scheduling
const int timeSlice = 4;

// Function to create a new process and add it to the ready queue
void createProcess(int pid, int burstTime) {
    PCB process;
    process.pid = pid;
    process.burstTime = burstTime;
    process.remainingTime = burstTime;
    readyQueue.push(process);
}

// Function to terminate the currently running process
void terminateProcess() {
    if (!readyQueue.empty()) {
        PCB process = readyQueue.front();
        readyQueue.pop();
        cout << "Process " << process.pid << " terminated." << endl;
    } else {
        cout << "No process to terminate." << endl;
    }
}

// Function to perform context switching and select the next process to run
void scheduleNextProcess() {
    if (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        readyQueue.pop();
        cout << "Switching from Process " << currentProcess.pid << endl;

        // Save the current process state if needed
        currentProcess.remainingTime -= timeSlice;
        if (currentProcess.remainingTime > 0) {
            cout << "Saving state of Process " << currentProcess.pid << endl;
            readyQueue.push(currentProcess);
        } else {
            cout << "Process " << currentProcess.pid << " completed." << endl;
        }

        // Select the next process to run
        if (!readyQueue.empty()) {
            PCB nextProcess = readyQueue.front();
            cout << "Switching to Process " << nextProcess.pid << endl;
        }
    } else {
        cout << "No process to schedule." << endl;
    }
}

int main() {
    // Create some example processes
    createProcess(1, 8);
    createProcess(2, 12);
    createProcess(3, 6);

    // Perform scheduling and context switching
    scheduleNextProcess();
    scheduleNextProcess();
    scheduleNextProcess();
    scheduleNextProcess();
    scheduleNextProcess();
    scheduleNextProcess();

    // Terminate a process
    terminateProcess();

    // Perform scheduling and context switching again
    scheduleNextProcess();
    scheduleNextProcess();
    scheduleNextProcess();

    return 0;
}