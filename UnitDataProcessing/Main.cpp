#include <iostream>
#include "heap_monitor.h"
#include "UnitDataProcessing.h"


int main()
{
    initHeapMonitor();
    std::wcout << "Hello World!\n";
    UnitDataProcessing* processApp = new UnitDataProcessing;
    processApp->load();
    processApp->start();

    delete processApp;
    return 0;
}