#include <iostream>
#include <queue>

// Process Control Block (PCB) structure
struct PCB {
    int process_id;
    std::string process_name;
    // Add any other required process attributes here

    //the ":" here is followed by what's called an initializer list
    //it allows for initializing member variables directly in the constructor's definition
    PCB(int id, const std::string& name) : process_id(id), process_name(name) {}
};

// Round Robin Scheduler
class Scheduler {
private:
    std::queue<PCB> ready_queue;
    int time_slice;

public:
    Scheduler(int slice) : time_slice(slice) {}

    // System call to create a new process
    void createProcess(int process_id, const std::string& process_name) {
        PCB new_process(process_id, process_name);
        ready_queue.push(new_process);
        std::cout << "Process \"" << process_name << "\" (ID " << process_id << ") created.\n";
    }

    // System call to terminate a process
    void terminateProcess() {
        if (!ready_queue.empty()) {
            PCB process = ready_queue.front();
            ready_queue.pop();
            std::cout << "Process \"" << process.process_name << "\" (ID " << process.process_id << ") terminated.\n";
        } else {
            std::cout << "No processes in the ready queue.\n";
        }
    }

    // Context switching functionality
    void contextSwitch() {
        if (!ready_queue.empty()) {
            PCB current_process = ready_queue.front();
            ready_queue.pop();
            ready_queue.push(current_process);
        }
    }

    // Run the scheduler
    void runScheduler() {
        if (!ready_queue.empty()) {
            PCB process = ready_queue.front();
            std::cout << "Running process \"" << process.process_name << "\" (ID " << process.process_id << ").\n";
            ready_queue.pop();
            std::cout << "Context switching...\n";
            contextSwitch();
            std::cout << "Next process in the ready queue.\n";
        } else {
            std::cout << "No processes in the ready queue.\n";
        }
    }
};

int main() {
    // Create a scheduler with time slice of 5
    Scheduler scheduler(5);

    // Create processes
    scheduler.createProcess(1, "Process A");
    scheduler.createProcess(2, "Process B");
    scheduler.createProcess(3, "Process C");
    std::cout << "\n";

    // Run the scheduler
    scheduler.runScheduler();
    scheduler.runScheduler();
    scheduler.runScheduler();
    scheduler.runScheduler();
    std::cout << "\n";

    // Terminate a process
    std::cout << "terminating a process\n";
    scheduler.terminateProcess();

    // Run the scheduler after termination
    scheduler.runScheduler();

    return 0;
}
