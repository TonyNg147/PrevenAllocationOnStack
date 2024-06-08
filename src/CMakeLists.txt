cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

project(Util)

set(SOURCES_WIN StackAllocationDetection_win.cpp)
set(SOURCES_UNIX StackAllocationDetection_unix.cpp)

add_library(${PROJECT_NAME} STATIC
    $<$<PLATFORM_ID:Windows>:${SOURCES_WIN}>
    $<$<PLATFORM_ID:Linux>:${SOURCES_UNIX}>
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PUBLIC $<$<PLATFORM_ID:Linux>:"-lpthread">)
