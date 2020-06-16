cmake_minimum_required(VERSION 3.12)
project(CPP_Workshop)

include("${CMAKE_CURRENT_SOURCE_DIR}/internal_commands.cmake")

set_compiler_options()

add_subdirectory(googletest)
add_subdirectory(UE)
add_subdirectory(BTS)
add_subdirectory(COMMON)
