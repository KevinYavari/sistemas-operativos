#include "SchedulerMLFQ.h"
#include <fstream>
#include <iomanip>

SchedulerMLFQ::SchedulerMLFQ(std::vector<std::pair<std::string,int>> config) {
    for (auto &c : config) {
        queues.push_back(new QueueMLFQ(c.first, c.second));
    }
    time = 0;
}

void SchedulerMLFQ::load_processes(std::vector<Process*>& processes) {
    for (auto &p : processes) {
        queues[p->queue - 1]->add_process(p, p->arrival);
    }
}

void SchedulerMLFQ::run() {
    while (true) {
        bool any = false;
        for (auto &q : queues) if (q->has_processes()) { any = true; break; }
        if (!any) break;

        bool executed = false;
        for (size_t i = 0; i < queues.size(); i++) {
            auto q = queues[i];
            if (q->has_processes()) {
                Process* proc = q->get_next();
                if (proc->start_time == -1) {
                    proc->start_time = time;
                    proc->response_time = time - proc->arrival;
                }

                int run_time;
                if (q->policy == "RR") run_time = std::min(proc->remaining, q->quantum);
                else if (q->policy == "SJF") run_time = proc->remaining;
                else if (q->policy == "STCF") run_time = 1;
                else run_time = proc->remaining;

                time += run_time;
                proc->remaining -= run_time;

                if (proc->remaining == 0) {
                    proc->completion_time = time;
                    proc->turnaround_time = proc->completion_time - proc->arrival;
                    proc->waiting_time = proc->turnaround_time - proc->burst;
                    finished.push_back(proc);
                } else {
                    if (q->policy == "RR" && i + 1 < queues.size()) {
                        queues[i+1]->add_process(proc, time);
                    } else if (q->policy == "STCF") {
                        q->add_process(proc, time);
                    } else {
                        q->add_process(proc, time);
                    }
                }
                executed = true;
                break;
            }
        }
        if (!executed) time++;
    }
}

void SchedulerMLFQ::save_report(const std::string& filename) {
    std::ofstream f(filename);
    f << "# archivo: " << filename << "\n";
    f << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    double avg_wt=0, avg_ct=0, avg_rt=0, avg_tat=0;
    for (auto &p : finished) {
        f << p->label << ";" << p->burst << ";" << p->arrival << ";"
          << p->queue << ";" << p->priority << ";"
          << p->waiting_time << ";" << p->completion_time << ";"
          << p->response_time << ";" << p->turnaround_time << "\n";
        avg_wt += p->waiting_time;
        avg_ct += p->completion_time;
        avg_rt += p->response_time;
        avg_tat += p->turnaround_time;
    }

    int n = finished.size();
    f << "\nWT=" << std::fixed << std::setprecision(1) << avg_wt/n
      << "; CT=" << avg_ct/n
      << "; RT=" << avg_rt/n
      << "; TAT=" << avg_tat/n << ";\n";
}
