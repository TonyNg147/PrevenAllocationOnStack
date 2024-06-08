#include <string.h>
#include <stdio.h>
#include <exception>
#include <stdexcept>
#include <StackAllocationDetection.h>

struct StackInfo
{
    char*  stackAddress = {};
    size_t stackSize = {};
};


class Object
{
    public:
        Object()
        {
            // We check if the address of the address belongs to the Stack allocated for object
            // that means the object is the stack object not the heap object
            if (util::isAllocatedOnTheThreadStack(this))
            {
                throw std::runtime_error("This object should be created on the heap. Not stack!");
            }
        }
};

void terminationHandler()
{
    if (auto excptr = std::current_exception())
    {
        try
        {
            std::rethrow_exception(excptr);
        }
        catch(const std::runtime_error& err)
        {
            fprintf(stderr,"Runtime error %s\n", err.what());
        }
        catch(...)
        {
            fprintf(stderr,"Undefined Exception\n");
        }
    }

    std::abort();
}

int main(int argc, char** argv)
{
    std::set_terminate(terminationHandler);
    Object *a = new Object();
    Object b;  // If we enable this line, it will generate an error
}
