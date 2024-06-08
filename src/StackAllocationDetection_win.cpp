#include "StackAllocationDetection.h"
#include <windows.h>
#include <processthreadsapi.h>
namespace util
{
    StackInfo getCurrentThreadStackInfo()
    {
        ULONG_PTR lowAddress;
        ULONG_PTR highAddress;

        GetCurrentThreadStackLimits(&lowAddress, &highAddress);

        return StackInfo{
            .lowAddress = reinterpret_cast<char*>(lowAddress),
            .highAddress = reinterpret_cast<char*>(highAddress)
        };
    }
};
