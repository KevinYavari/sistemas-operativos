#include "Utils.h"
#include "SchedulerMLFQ.h"
#include "Process.h"
#include <iostream>

int main() {
    auto procesos = read_processes("mlfq003.txt");

    // Configuración 1
    std::vector<std::pair<std::string,int>> config1 = {{"RR",1},{"RR",3},{"RR",4},{"SJF",0}};
    SchedulerMLFQ sched1(config1);
    sched1.load_processes(procesos);
    sched1.run();
    sched1.save_report("mlfq001Out.txt");

    // Configuración 2
    auto procesos2 = read_processes("mlfq001.txt");
    std::vector<std::pair<std::string,int>> config2 = {{"RR",2},{"RR",3},{"RR",4},{"STCF",0}};
    SchedulerMLFQ sched2(config2);
    sched2.load_processes(procesos2);
    sched2.run();
    sched2.save_report("mlq002Out.txt");

    // Configuración 3
    auto procesos3 = read_processes("mlfq001.txt");
    std::vector<std::pair<std::string,int>> config3 = {{"RR",3},{"RR",5},{"RR",6},{"RR",20}};
    SchedulerMLFQ sched3(config3);
    sched3.load_processes(procesos3);
    sched3.run();
    sched3.save_report("mlq003Out.txt");

    std::cout << "Simulacion terminada. Revisa los archivos de salida.\n";
    return 0;
}
