cmake_minimum_required(VERSION 3.20)
project(raccoonOS
    VERSION 0.0.1
    LANGUAGES C CXX ASM_NASM
)

set(ENV{PATH} "$ENV{PWD}/build/cross/bin:$ENV{PATH}")
set(CROSS_DIR "${CMAKE_SOURCE_DIR}/meta")

# set a target to compile to (default x64).
set(TARGET "x86_64-elf")
# set a loader to target (default limine)
set(LOADER "limine")

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AR           "${CROSS_DIR}/cross/${TARGET}-ar")
set(CMAKE_C_COMPILER   "${CROSS_DIR}/cross/${TARGET}-gcc")
set(CMAKE_CXX_COMPILER "${CROSS_DIR}/cross/${TARGET}-g++")
set(CMAKE_OBJCOPY      "${CROSS_DIR}/cross/${TARGET}-objcopy")

add_compile_options("-O2" "-g" "-Wall" "-Wextra")
set(CPPFLAGS)
set(GLOBAL_INCLUDE "${CMAKE_SOURCE_DIR}/include")

set(SUBDIRS "kernel")

foreach(SUBDIR IN LISTS SUBDIRS)
    message(STATUS "adding subdirectory ${SUBDIR}")
    add_subdirectory("${SUBDIR}")
endforeach()