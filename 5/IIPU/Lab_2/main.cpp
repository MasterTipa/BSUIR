//#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    MEMORYSTATUSEX ms;
    _MEMORY_BASIC_INFORMATION mbi;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);
    cout << "   MEMORYSTATUSEX: " << endl;
    cout << "Всего памяти: " << ms.ullTotalPhys << endl;
    cout << "dwLength: " << ms.dwLength << endl;
    cout << "ullAvailVirtual: " << ms.ullAvailVirtual << endl;
    cout << "dwMemoryLoad: " << ms.dwMemoryLoad << endl;
    cout << "ullAvailExtendedVirtual: " << ms.ullAvailExtendedVirtual << endl;
    cout << "ullAvailPageFile: " << ms.ullAvailPageFile << endl;
    cout << "ullAvailPhys: " << ms.ullAvailPhys << endl;
    cout << "ullTotalPageFile: " << ms.ullTotalPageFile << endl;
    cout << "ullTotalPhys: " << ms.ullTotalPhys << endl;
    cout << "   _MEMORY_BASIC_INFORMATION: " << endl;
    cout << "AllocationBase: " << mbi.AllocationBase << endl;
    cout << "AllocationProtect: " << mbi.AllocationProtect << endl;
    cout << "Protect: " << mbi.Protect << endl;
    cout << "RegionSize: " << mbi.RegionSize << endl;
    cout << "State: " << mbi.State << endl;
    cout << "Type: " << mbi.Type << endl;
    cout << "BaseAddress: " << mbi.BaseAddress << endl;
    system("pause");
    return 0;
}