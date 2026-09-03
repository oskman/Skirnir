#pragma once
#include <windows.h>

namespace skirnir::win {
    inline ULONGLONG FileTime_to_uint(const FILETIME& filetime) {
        return (static_cast<ULONGLONG>(filetime.dwHighDateTime) << 32) | filetime.dwLowDateTime; //highdatetime er 32 bit, så caster til 64 bit usignert type, flytter deretter highdate bitene 32 plasser til venstre. Nå er halvparten til høyre bare 0-ere, henter deretter 32 bit lowdatetime og "or-er" de mot alle 0 bitene på høyre halvdel. Hvis 1 i lowdate blir 1or0=1, hvis 0 i lowdate blir 0or0=0 (bitwise or).
}
}