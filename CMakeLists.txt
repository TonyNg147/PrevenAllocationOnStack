cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if (ENABLE_TEST)
    add_subdirectory(test)
    add_dependencies(StackAllocationChecking Util)
endif()

