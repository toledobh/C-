#include "process.h"

Process::Process(int pid, string pname, int bTime){
    processId = pid;
    processName = pname;
    burstTime = bTime;
    remainingTime = bTime;
}

int Process::getProcessId() {
    return processId;
}

string Process::getProcessName() {
    return processName;
}

int Process::getBurstTime() {
    return burstTime;
}

int Process::getRemainingTime() {
    return remainingTime;
}

void Process::setProcessId(int id){
    processId = id;
}

void Process::setProcessName(string name){
    processName = name;
}

void Process::setBurstTime(int time){
    burstTime = time;
}

void Process::deductTimeSlice(int timeSlice) {
    remainingTime -= timeSlice;
}

bool Process::isCompleted() {
    return remainingTime <= 0;
}