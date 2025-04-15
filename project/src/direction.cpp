#include "direction.hpp"
#include <plog/Log.h>

Direction opposite_direction(Direction direction)
{
    switch (direction) {
    case Direction::DOWN:
        return Direction::UP;
    case Direction::UP:
        return Direction::DOWN;
    case Direction::LEFT:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::LEFT;
    default:
        PLOG_ERROR << "Unhandled direction!";
        std::abort();
    }
}

Direction left_direction(Direction direction)
{
    switch (direction) {
    case Direction::LEFT:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::UP;
    case Direction::UP:
        return Direction::LEFT;
    default:
        PLOG_ERROR << "Unhandled direction";
        std::abort();
    }
}

Direction right_direction(Direction direction)
{
    switch (direction) {
    case Direction::LEFT:
        return Direction::UP;
    case Direction::UP:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::LEFT;
    default:
        PLOG_ERROR << "Unhandled direction";
        std::abort();
    }
}

bool is_direction(std::string str)
{
    return str == DIRECTION_RIGHT || str == DIRECTION_FORWARD || str == DIRECTION_LEFT || str == DIRECTION_BACK;
}

Direction string_to_direction(std::string str, Direction look_dir)
{
    if (str == DIRECTION_FORWARD)
        return look_dir;
    else if (str == DIRECTION_BACK)
        return opposite_direction(look_dir);
    else if (str == DIRECTION_LEFT)
        return left_direction(look_dir);
    else if (str == DIRECTION_RIGHT)
        return right_direction(look_dir);
    else {
        PLOG_ERROR << "Invalid direction";
        return look_dir;
    }
}

bool calc_position(size_t old_x, size_t old_y, Direction direction, size_t& new_x, size_t& new_y)
{
    switch (direction) {
    case Direction::UP:
        new_x = old_x;
        new_y = old_y + 1;
        break;
    case Direction::DOWN:
        new_x = old_x;
        new_y = old_y - 1;
        break;
    case Direction::LEFT:
        new_x = old_x - 1;
        new_y = old_y;
        break;
    case Direction::RIGHT:
        new_x = old_x + 1;
        new_y = old_y;
        break;
    }

    return new_x < FIELD_SIZE && new_y < FIELD_SIZE;
}