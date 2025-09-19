#ifndef UTILS_H
#define UTILS_H

#include "Process.h"
#include <vector>
#include <string>

std::vector<Process*> read_processes(const std::string& filename);

#endif
