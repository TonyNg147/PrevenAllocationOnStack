
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>

struct StackInfo
{
    char*  stackAddress = {};
    size_t stackSize = {};
};

static StackInfo
display_stack_related_attributes(pthread_t thread)
{
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

    return {reinterpret_cast<char*>(stack_addr), stack_size};
}

class Object
{
    public:
        Object()
        {
            // We check if the address of the address belongs to the Stack allocated for object
            // that means the object is the stack object not the heap object
            if (isAllocatedOnTheThreadStack(this))
            {
                throw std::runtime_error("This object should be created on the heap. Not stack!");
            }
        }

        static bool isAllocatedOnTheThreadStack(void* ptr)
        {


            StackInfo info = display_stack_related_attributes(pthread_self());


            char* lowAddress   = info.stackAddress;
            char* highAddress  = lowAddress + info.stackSize;
            char* objectAddress  = reinterpret_cast<char*>(ptr);

            return lowAddress <= objectAddress && objectAddress <= highAddress;
        }
};

int main()
{
    Object *a = new Object();
    // Object b;  // If we enable this line, it will generate an error
}