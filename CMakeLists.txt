cmake_minimum_required(VERSION 3.20)
project(raccoonOS
    VERSION 0.0.1
    LANGUAGES C CXX ASM_NASM
)

set(ENV{PATH} "$ENV{PWD}/build/cross/bin:$ENV{PATH}")

# set a target to compile to (default x64).
option(TARGET "x86_64-elf")

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_C_STANDARD 18)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AR "${CMAKE_BINARY_DIR}/../cross/${TARGET}-ar")
set(CMAKE_C_COMPILER "${CMAKE_BINARY_DIR}/../cross/${TARGET}-gcc")
set(CMAKE_CXX_COMPILER "${CMAKE_BINARY_DIR}/../cross/${TARGET}-g++")

set(CFLAGS "-O2" "-g")
set(CPPFLAGS)

set(SUBDIRS "libc kernel")

foreach(SUBDIR IN LISTS ${SUBDIRS})
    add_subdirectory("${SUBDIR}")
endforeach()