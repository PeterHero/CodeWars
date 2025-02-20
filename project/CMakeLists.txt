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
    "${INCLUDE_DIR}/battle_controller.hpp"
    "${INCLUDE_DIR}/direction.hpp"
    "${INCLUDE_DIR}/field_object.hpp"
    "${INCLUDE_DIR}/robot.hpp"
    )
set(TARGET_SRC
    "${SRC_DIR}/hello_main.cpp"
    "${SRC_DIR}/battle_controller.cpp"
    "${SRC_DIR}/direction.cpp"
    "${SRC_DIR}/field_object.cpp"
    "${SRC_DIR}/robot.cpp"
    )

add_executable(${MY_EXE} ${TARGET_H} ${TARGET_SRC})

target_include_directories(${MY_EXE} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${MY_EXE} PRIVATE plog::plog)

set_property(TARGET ${MY_EXE} PROPERTY CXX_STANDARD 23)
