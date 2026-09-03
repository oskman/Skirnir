#pragma once

#include <string>

namespace skirnir {
    class SystemMonitor {
        public:
            SystemMonitor();
            ~SystemMonitor();

            double get_cpu_usage();
            double get_memory_usage();
            std::string get_os_name();

        private:

    };
}