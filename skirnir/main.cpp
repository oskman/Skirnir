#include <iostream>
#include "systemMonitor.hpp"

int main()
{
	SystemMonitor sysmon;

    std::cout << "Memory usage: " << sysmon.get_memory_usage() << "%" << '\n';
    std::cout << "CPU usage: " << sysmon.get_cpu_usage() << "%" << '\n';
	return 0;
}