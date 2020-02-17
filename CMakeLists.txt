cmake_minimum_required (VERSION 2.6)

project (elf_viewer)

set(CMAKE_C_FLAGS "-m32")

add_executable(elf_viewer elf_viewer.c)
