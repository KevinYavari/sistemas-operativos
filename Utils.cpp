#include "Utils.h"
#include <fstream>
#include <sstream>

std::vector<Process*> read_processes(const std::string& filename) {
    std::vector<Process*> processes;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
        std::string label, bt, at, q, pr;
        if (std::getline(ss, label, ';') &&
            std::getline(ss, bt, ';') &&
            std::getline(ss, at, ';') &&
            std::getline(ss, q, ';') &&
            std::getline(ss, pr, ';')) {
            processes.push_back(new Process(label, std::stoi(bt), std::stoi(at),
                                            std::stoi(q), std::stoi(pr)));
        }
    }
    return processes;
}
