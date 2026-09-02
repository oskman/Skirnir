#include "systemMonitor.hpp"
#include <windows.h>
#include <psapi.h>

#define DIV 1024
#define WIDTH 7

SystemMonitor::SystemMonitor() {}
SystemMonitor::~SystemMonitor() {}

//TODO: lag en/flere service tjenester fremfor alt i en fil
ULONGLONG FileTime_to_uint(const FILETIME& filetime) {
    return (static_cast<ULONGLONG>(filetime.dwHighDateTime) << 32) | filetime.dwLowDateTime; //highdatetime er 32 bit, så caster til 64 bit usignert type, flytter deretter highdate bitene 32 plasser til venstre. Nå er halvparten til høyre bare 0-ere, henter deretter 32 bit lowdatetime og "or-er" de mot alle 0 bitene på høyre halvdel. Hvis 1 i lowdate blir 1or0=1, hvis 0 i lowdate blir 0or0=0 (bitwise or).
}

double SystemMonitor::get_cpu_usage() {
   FILETIME idleTimeSnap1,kernelTimeSnap1, userTimeSnap1;
   FILETIME idleTimeSnap2,kernelTimeSnap2, userTimeSnap2;

   GetSystemTimes(&idleTimeSnap1, &kernelTimeSnap1, &userTimeSnap1);
   Sleep(100); //kanskje finne en måte å lagre snapshottene når en instans av systemonitor starter isteden, så hver gang getcpuusage kalles, så lagrer den snap2 og sjekker mot snap1, etter det settes snap2 til snap1 (kanskje kall snap1 prev_snap). For å slippe å bruke sleep
   GetSystemTimes(&idleTimeSnap2, &kernelTimeSnap2, &userTimeSnap2);

   ULONGLONG idle = FileTime_to_uint(idleTimeSnap2) - FileTime_to_uint(idleTimeSnap1);
   ULONGLONG kernel = FileTime_to_uint(kernelTimeSnap2) - FileTime_to_uint(kernelTimeSnap1);
   ULONGLONG user = FileTime_to_uint(userTimeSnap2) - FileTime_to_uint(userTimeSnap1);

   ULONGLONG total = (kernel+user);
   
   return static_cast<double>(total-idle) / total*100.0;
}

double SystemMonitor::get_memory_usage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    GlobalMemoryStatusEx(&memInfo);

    return static_cast<double>(memInfo.dwMemoryLoad);
}