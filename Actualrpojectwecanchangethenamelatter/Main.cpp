int main() {
    MyThreadManager threadManager;

    threadManager.createThread();
    threadManager.scheduleThread();
    threadManager.synchronizeThreads();
    threadManager.terminateThread();

    return 0;
}