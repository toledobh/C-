#ifndef process_h
#define process_h

#include <string>  
using namespace std;

class Process {
    private:
        // Atributes
        int processId;
        string processName;
        int burstTime;
        int remainingTime;

    public:
        // Constructor
        Process(int pid, string pname, int bTime);
        
        // Getter methods
        int getProcessId();
        string getProcessName();
        int getBurstTime();
        int getRemainingTime();

        // Set methods
        void setProcessId(int id);
        void setProcessName(string name);
        void setBurstTime(int time);

        // Other methods
        bool isCompleted();
        void deductTimeSlice(int timeSlice);
};

#endif

