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
    "${INCLUDE_DIR}/character.hpp"
    "${INCLUDE_DIR}/command.hpp"
    "${INCLUDE_DIR}/commands.hpp"
    "${INCLUDE_DIR}/command_factory.hpp"
    "${INCLUDE_DIR}/direction.hpp"
    "${INCLUDE_DIR}/field_object.hpp"
    "${INCLUDE_DIR}/field_objects.hpp"
    "${INCLUDE_DIR}/interpreter.hpp"
    "${INCLUDE_DIR}/robot_actions.hpp"
    "${INCLUDE_DIR}/robot_events.hpp"
    "${INCLUDE_DIR}/robot_info.hpp"
    "${INCLUDE_DIR}/robot.hpp"
    "${INCLUDE_DIR}/rotation.hpp"
    )
set(TARGET_SRC
    "${SRC_DIR}/battle_controller.cpp"
    "${SRC_DIR}/command_factory.cpp"
    "${SRC_DIR}/direction.cpp"
    "${SRC_DIR}/interpreter.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/robot.cpp"
    "${SRC_DIR}/rotation.cpp"
    )

add_executable(${MY_EXE} ${TARGET_H} ${TARGET_SRC})

target_include_directories(${MY_EXE} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${MY_EXE} PRIVATE plog::plog)

set_property(TARGET ${MY_EXE} PROPERTY CXX_STANDARD 23)
