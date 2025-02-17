#
# This is the cmake project file for Hello World
#

cmake_minimum_required (VERSION 3.20)

project("hello_world")

set(MY_EXE "hello")

add_subdirectory(vendor/plog)

add_executable(${MY_EXE} "hello_main.cpp" "hello_functions.cpp" "hello_functions.hpp")

target_link_libraries(${MY_EXE} PRIVATE plog::plog)

set_property(TARGET ${MY_EXE} PROPERTY CXX_STANDARD 23)
