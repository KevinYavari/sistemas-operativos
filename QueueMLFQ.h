#ifndef QUEUE_MLFQ_H
#define QUEUE_MLFQ_H

#include "Process.h"
#include <deque>
#include <queue>
#include <string>
#include <vector>

struct ProcWrapper {
    int key;        // puede ser burst o remaining
    int arrival;
    Process* p;

    ProcWrapper(int k, int a, Process* proc) : key(k), arrival(a), p(proc) {}
};

// Comparador para priority_queue (min-heap)
struct CompareProc {
    bool operator()(const ProcWrapper& a, const ProcWrapper& b) const {
        if (a.key == b.key) return a.arrival > b.arrival;
        return a.key > b.key; // menor key tiene prioridad
    }
};

class QueueMLFQ {
public:
    std::string policy;  // "RR", "SJF", "STCF"
    int quantum;

    std::deque<Process*> rrQueue;
    std::priority_queue<ProcWrapper, std::vector<ProcWrapper>, CompareProc> heapQueue;

    QueueMLFQ(std::string pol, int q);

    void add_process(Process* p, int current_time);
    Process* get_next();
    bool has_processes();
};

#endif
