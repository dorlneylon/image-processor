cmake_minimum_required(VERSION 3.24)
project(assignment-sepia C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-std=c17 -O2 -march=native -F dwarf -no-pie -Wall -Wextra -Wpedantic -Werror -g3 -ggdb")

add_executable(assignment-sepia src/main.c)
target_include_directories(assignment-sepia PRIVATE include)

file(GLOB SOURCES "src/*.c")
target_sources(assignment-sepia PRIVATE ${SOURCES})

