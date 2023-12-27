cmake_minimum_required(VERSION 3.24)
project(assignment-sepia C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-std=c17 -no-pie -Wall -Wextra -Wpedantic -Werror -g3 -ggdb")

add_executable(assignment-sepia src/main.c src/process.c src/compare.c)

target_include_directories(assignment-sepia PRIVATE include)

add_custom_target(run
    COMMAND assignment-sepia ./input.bmp ./output.bmp
    DEPENDS assignment-sepia
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
