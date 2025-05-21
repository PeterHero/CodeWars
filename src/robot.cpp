#include "robot.hpp"
#include "field_objects.hpp"
#include <plog/Log.h>

/**
 * @brief Construct a new Robot:: Robot object - default constructor
 *
 */
Robot::Robot()
    : _is_alive(false)
{
}

/**
 * @brief Print robot to stream
 *
 * @param stream
 */
void Robot::print(std::ostream& stream) const
{
    switch (_look_dir) {
    case Direction::LEFT:
        stream << std::string("<");
        break;
    case Direction::UP:
        stream << std::string("A");
        break;
    case Direction::RIGHT:
        stream << std::string(">");
        break;
    case Direction::DOWN:
        stream << std::string("V");
        break;
    }
}

/**
 * @brief Print robot to stream
 *
 * @param stream
 * @param robot
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& stream, Robot& robot)
{
    robot.print(stream);
    return stream;
}