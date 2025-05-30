cmake_minimum_required(VERSION 3.10)
project(PokerEngine)

set(CMAKE_CXX_STANDARD 17)

# Include headers from include/
include_directories(include)

# Add all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

add_executable(poker ${SOURCES})