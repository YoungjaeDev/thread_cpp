cmake_minimum_required(VERSION 3.16)

project(my_project)

# set(TBB_DIR ${CMAKE_SOURCE_DIR}/external/vcpkg/packages/tbb_x64-linux/share/tbb)

# find_package(TBB REQUIRED)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files here
set(SOURCES async4.cpp)

# Add an executable target for your program
add_executable(my_program ${SOURCES})

# Link against the threading library
find_package(Threads REQUIRED)
target_link_libraries(my_program PRIVATE Threads::Threads)
