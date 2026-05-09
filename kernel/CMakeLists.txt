cmake_minimum_required(VERSION 3.20)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(KERNEL_C_FLAGS "-ffreestanding -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2")

file(GLOB_RECURSE CORE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/core/*.c")

add_executable(kernel ${CORE_SRC})