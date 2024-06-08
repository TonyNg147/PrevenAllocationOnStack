#include "StackAllocationDetection.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


namespace util
{
    StackInfo getCurrentThreadStackInfo()
    {
        pthread_t thread = pthread_self();

        pthread_attr_t attr;

        if (pthread_getattr_np(thread, &attr) != 0)
        {
            fprintf(stderr, "Error when initializing stack attribute %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        void *stack_addr;
        size_t stack_size = {};

        if (pthread_attr_getstack(&attr, &stack_addr, &stack_size) != 0)
        {
            fprintf(stderr, "Error when getting stack attribute %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        (void)pthread_attr_destroy(&attr);

        char* lowAddressConversion = reinterpret_cast<char*>(stack_addr);

        return StackInfo{
            .lowAddress = lowAddressConversion,
            .highAddress = lowAddressConversion + stack_size
        };
    }
};

