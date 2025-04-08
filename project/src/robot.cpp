#include "robot.hpp"

Robot::Robot()
    : control_script("")
{
}

Robot::Robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction, std::string script_file)
    : _id(id)
    , _health(ROBOT_MAX_HEALTH)
    , _pos_x(pos_x)
    , _pos_y(pos_y)
    , _look_dir(direction)
    , control_script(Interpret(script_file))
{
}

void Robot::turn_left()
{
    switch (_look_dir) {
    case Direction::LEFT:
        _look_dir = Direction::DOWN;
        break;
    case Direction::UP:
        _look_dir = Direction::LEFT;
        break;
    case Direction::RIGHT:
        _look_dir = Direction::UP;
        break;
    case Direction::DOWN:
        _look_dir = Direction::RIGHT;
        break;
    }
}

void Robot::turn_right()
{
    switch (_look_dir) {
    case Direction::LEFT:
        _look_dir = Direction::UP;
        break;
    case Direction::UP:
        _look_dir = Direction::RIGHT;
        break;
    case Direction::RIGHT:
        _look_dir = Direction::DOWN;
        break;
    case Direction::DOWN:
        _look_dir = Direction::LEFT;
        break;
    }
}

void Robot::print(std::ostream& stream) const
{
    switch (_look_dir) {
    case Direction::LEFT:
        stream << "<";
        break;
    case Direction::UP:
        stream << "A";
        break;
    case Direction::RIGHT:
        stream << ">";
        break;
    case Direction::DOWN:
        stream << "V";
        break;
    }
}

std::ostream& operator<<(std::ostream& stream, Robot& robot)
{
    robot.print(stream);
    return stream;
}
