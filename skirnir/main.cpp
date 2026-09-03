#include <iostream>
#include <chrono>
#include <thread>
#include "systemMonitor.hpp"


#define CLEAR_SCREEN "\033[2J"
#define MOVE_CURSOR_HOME "\033[H"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

int main()
{
	skirnir::SystemMonitor sysmon;

    std::cout << HIDE_CURSOR;

    std::cout << CLEAR_SCREEN;
    for (int i = 0; i < 50; ++i) {
        std::cout << MOVE_CURSOR_HOME;
        std::cout << "===============================\n";
        std::cout << "         SKIRNIR MONITOR       \n";
        std::cout << "===============================\n";
        std::cout << "Memory usage: " << sysmon.get_memory_usage() << "%" << '\n';
        std::cout << "CPU usage: " << sysmon.get_cpu_usage() << "%" << '\n';
        std::cout << "===============================\n";

        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
	return 0;
}