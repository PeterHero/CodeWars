#include "direction.hpp"

bool is_direction(std::string str)
{
    return str == DIRECTION_RIGHT || str == DIRECTION_DOWN || str == DIRECTION_LEFT || str == DIRECTION_UP;
}

Direction string_to_direction(std::string str)
{
    if (str == DIRECTION_RIGHT)
        return Direction::RIGHT;
    else if (str == DIRECTION_DOWN)
        return Direction::DOWN;
    else if (str == DIRECTION_LEFT)
        return Direction::LEFT;
    else
        return Direction::UP;
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