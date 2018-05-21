cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

#set (CMAKE_BUILD_TYPE "Debug;Release")
set (CMAKE_CONFIGURATION_TYPES "Debug;Release")
set (CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0")
set (CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")

project (allocator)
add_executable(allocator main.cc)

add_subdirectory(ext/memory)
target_link_libraries(allocator PUBLIC foonathan_memory)


