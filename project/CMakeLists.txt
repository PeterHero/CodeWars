#
# This is the cmake project file for Hello World
#

cmake_minimum_required (VERSION 3.20)

project("code_wars")

add_subdirectory(vendor/plog)

set(MY_EXE "code_wars")
set(INCLUDE_DIR "include")
set(SRC_DIR "src")

set(TARGET_H
    "${INCLUDE_DIR}/hello_functions.hpp"
    "${INCLUDE_DIR}/battle_controller.hpp"
    )
set(TARGET_SRC
    "${SRC_DIR}/hello_main.cpp"
    "${SRC_DIR}/hello_functions.cpp"
    "${SRC_DIR}/battle_controller.cpp"
    )

add_executable(${MY_EXE} ${TARGET_H} ${TARGET_SRC})

target_include_directories(${MY_EXE} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${MY_EXE} PRIVATE plog::plog)

set_property(TARGET ${MY_EXE} PROPERTY CXX_STANDARD 23)
