#include "Process.h"

Process::Process(std::string l, int bt, int at, int q, int pr)
    : label(l), burst(bt), arrival(at), queue(q), priority(pr) {
    remaining = burst;
    start_time = -1;
    completion_time = -1;
    response_time = -1;
    waiting_time = 0;
    turnaround_time = 0;
}
