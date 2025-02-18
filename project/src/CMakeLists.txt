#
# This is the cmake project file for Hello World
#

cmake_minimum_required (VERSION 3.20)

project("hello_world")

add_subdirectory(vendor/plog)

set(MY_EXE "hello")
set(TARGET_H
    "hello_functions.hpp"
    "battle_controller.hpp"
    )
set(TARGET_SRC
    "hello_main.cpp"
    "hello_functions.cpp"
    "battle_controller.cpp"
    )

add_executable(${MY_EXE} ${TARGET_H} ${TARGET_SRC})

target_link_libraries(${MY_EXE} PRIVATE plog::plog)

set_property(TARGET ${MY_EXE} PROPERTY CXX_STANDARD 23)
