#include "systemMonitor.hpp"
#include "winUtils.hpp"
#include <windows.h>
#include <psapi.h>


#define DIV 1024
#define WIDTH 7

namespace skirnir {
    SystemMonitor::SystemMonitor() {}
    SystemMonitor::~SystemMonitor() {}



    double SystemMonitor::get_cpu_usage() {
    FILETIME idleTimeSnap1,kernelTimeSnap1, userTimeSnap1;
    FILETIME idleTimeSnap2,kernelTimeSnap2, userTimeSnap2;

    GetSystemTimes(&idleTimeSnap1, &kernelTimeSnap1, &userTimeSnap1);
    Sleep(100); //kanskje finne en måte å lagre snapshottene når en instans av systemonitor starter isteden, så hver gang getcpuusage kalles, så lagrer den snap2 og sjekker mot snap1, etter det settes snap2 til snap1 (kanskje kall snap1 prev_snap). For å slippe å bruke sleep
    GetSystemTimes(&idleTimeSnap2, &kernelTimeSnap2, &userTimeSnap2);

    ULONGLONG idle = win::FileTime_to_uint(idleTimeSnap2) - win::FileTime_to_uint(idleTimeSnap1);
    ULONGLONG kernel = win::FileTime_to_uint(kernelTimeSnap2) - win::FileTime_to_uint(kernelTimeSnap1);
    ULONGLONG user = win::FileTime_to_uint(userTimeSnap2) - win::FileTime_to_uint(userTimeSnap1);

    ULONGLONG total = (kernel+user);
    
    return static_cast<double>(total-idle) / total*100.0;
    }

    double SystemMonitor::get_memory_usage() {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);

        GlobalMemoryStatusEx(&memInfo);

        return static_cast<double>(memInfo.dwMemoryLoad);
    }
}