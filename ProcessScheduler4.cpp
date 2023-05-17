#include <iostream>
#include <queue>
#include <chrono>

struct PCB {
    int id;
};

std::queue<PCB> readyQueue;
const int timeSlice = 500000000000; //500ms

void createProcess(int id) {
    PCB process;
    process.id = id;
    readyQueue.push(process);
    std::cout << "Process " << process.id << " created." << std::endl;

}

void terminateProcess() {
    if (!readyQueue.empty()) {
        PCB process = readyQueue.front();
        readyQueue.pop();
        std::cout << "Process " << process.id << " terminated." << std::endl;
    } else {
        std::cout << "No process to terminate." << std::endl;
    }
}

void contextSwitch() {
    if (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        readyQueue.pop();
        readyQueue.push(currentProcess);
    }
}

void runScheduler() {    
    while (!readyQueue.empty()) {
        auto start = std::chrono::high_resolution_clock::now();
        auto current = std::chrono::high_resolution_clock::now();
        int durration = std::chrono::duration_cast<std::chrono::nanoseconds>(current-start).count();
        while (durration < timeSlice) {
            auto current = std::chrono::high_resolution_clock::now();
            durration = std::chrono::duration_cast<std::chrono::nanoseconds>(current-start).count();  
        }
        contextSwitch();
        terminateProcess();
    }
}