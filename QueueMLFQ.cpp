#include "QueueMLFQ.h"

QueueMLFQ::QueueMLFQ(std::string pol, int q) {
    policy = pol;
    quantum = q;
}

void QueueMLFQ::add_process(Process* p, int current_time) {
    if (policy == "SJF") {
        heapQueue.push(ProcWrapper(p->burst, p->arrival, p));
    } else if (policy == "STCF") {
        heapQueue.push(ProcWrapper(p->remaining, p->arrival, p));
    } else { // RR
        rrQueue.push_back(p);
    }
}

Process* QueueMLFQ::get_next() {
    if (policy == "SJF" || policy == "STCF") {
        if (heapQueue.empty()) return nullptr;
        ProcWrapper wrap = heapQueue.top();
        heapQueue.pop();
        return wrap.p;
    } else {
        if (rrQueue.empty()) return nullptr;
        Process* p = rrQueue.front();
        rrQueue.pop_front();
        return p;
    }
}

bool QueueMLFQ::has_processes() {
    return (!rrQueue.empty() || !heapQueue.empty());
}
