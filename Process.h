#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    std::string label;
    int burst;
    int arrival;
    int queue;
    int priority;

    int remaining;
    int start_time;
    int completion_time;
    int response_time;
    int waiting_time;
    int turnaround_time;

    Process(std::string l, int bt, int at, int q, int pr);
};

#endif
