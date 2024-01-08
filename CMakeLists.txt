cmake_minimum_required(VERSION 3.24)
project(image_transformer C)
enable_language(ASM_NASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-std=c17 -O2 -lm -march=native -msse -msse2 -mavx2 -F dwarf -no-pie -Wall -Wextra -Wpedantic -Werror -g3 -ggdb")
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS asm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

add_executable(image_transformer src/main.c src/sepia_asm.asm)
target_include_directories(image_transformer PRIVATE include)
set_source_files_properties(src/sepia_asm.asm PROPERTIES LANGUAGE ASM_NASM)

file(GLOB SOURCES "src/*.c")
target_sources(image_transformer PRIVATE ${SOURCES})
