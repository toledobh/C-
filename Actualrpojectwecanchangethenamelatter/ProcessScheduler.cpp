#include <iostream>
#include <queue>

//process control block
struct PCB {
    int id;
    int burstTime;
};

//queue to hold the ready processes
std::queue<PCB> readyQueue;

//timeslice to control the processes
const int timeSlice = 1;

//method to create a new process and push it into the ready queue
void createProcess(int id, int burstTime) {
    PCB process;
    process.id = id;
    process.burstTime = burstTime;
    readyQueue.push(process);
    std::cout << "Process " << process.id << " created." << std::endl;

}

//method to take a process out of the ready queue
void terminateProcess() {
    if (!readyQueue.empty()) {
        PCB process = readyQueue.front();
        readyQueue.pop();
        std::cout << "Process " << process.id << " terminated." << std::endl;
    } else {
        std::cout << "No process to terminate." << std::endl;
    }
}

//method to switch between processes
//will subtract from the current process's burst time
void contextSwitch() {
    if (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        currentProcess.burstTime -= timeSlice;
        readyQueue.pop();
        readyQueue.push(currentProcess);
    }
}

//method to run the processes in the ready queue
//will terminate processes when their burst time reaches zero
void runProcesses() {
    while (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        if (currentProcess.burstTime < 1) {
            terminateProcess();
        }
        contextSwitch();
    }
}

int main() {
    createProcess(1, 12);
    createProcess(2, 2);
    createProcess(3, 4);

    runProcesses();
}