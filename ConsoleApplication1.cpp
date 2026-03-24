// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include<string>

float GetCPULoad() {
    static FILETIME idleTimePrev = {}, kernelTimePrev = {}, userTimePrev = {};

    FILETIME idleTime, kernelTime, userTime;
    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) return 0.0;

    auto toUInt64 = [](FILETIME ft) {
        return ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
        };

    uint64_t idleDiff = toUInt64(idleTime) - toUInt64(idleTimePrev);
    uint64_t kernelDiff = toUInt64(kernelTime) - toUInt64(kernelTimePrev);
    uint64_t userDiff = toUInt64(userTime) - toUInt64(userTimePrev);

    idleTimePrev = idleTime;
    kernelTimePrev = kernelTime;
    userTimePrev = userTime;

    uint64_t total = kernelDiff + userDiff;
    return total ? (1.0 - (float)idleDiff / total) * 100.0 : 0.0;
}




int main()
{
    unsigned int c = 0;
    std::string consoleline = "";
    while (c!=10) {
        consoleline=std::to_string(GetCPULoad());

        std::cout << consoleline<<"\n";
        c++;
        Sleep(1000);
    }
    
    return 0;
}
