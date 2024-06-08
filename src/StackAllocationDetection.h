#pragma once

namespace util
{
    struct StackInfo
    {
        char* lowAddress;
        char* highAddress;
        int size;
    };

    StackInfo getCurrentThreadStackInfo();

    inline bool isAllocatedOnTheThreadStack(void* ptr)
    {
        StackInfo stackInfo = getCurrentThreadStackInfo();
        char* objAddress = reinterpret_cast<char*>(ptr);
        return stackInfo.lowAddress <= objAddress && objAddress <= stackInfo.highAddress;
    }
};