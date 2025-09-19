#ifndef SCHEDULER_MLFQ_H
#define SCHEDULER_MLFQ_H

#include "QueueMLFQ.h"
#include <vector>
#include <string>

class SchedulerMLFQ {
public:
    std::vector<QueueMLFQ*> queues;
    int time;
    std::vector<Process*> finished;

    SchedulerMLFQ(std::vector<std::pair<std::string,int>> config);
    void load_processes(std::vector<Process*>& processes);
    void run();
    void save_report(const std::string& filename);
};

#endif
