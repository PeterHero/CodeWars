#include "declarations.hpp"

std::string to_string(Direction& direction)
{
    switch (direction) {
    case Direction::LEFT:
        return "left";
    case Direction::UP:
        return "up";
    case Direction::RIGHT:
        return "right";
    case Direction::DOWN:
        return "down";
    }

    return "error";
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
