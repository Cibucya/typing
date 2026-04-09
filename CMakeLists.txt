# CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(SpeedTest VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(SpeedTest ${SOURCES})

# Optional: Link additional libraries if needed
# target_link_libraries(MyProject <library>)