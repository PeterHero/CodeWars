#ifndef direction_hpp_
#define direction_hpp_

#include <string>

#define FIELD_SIZE 5
#define DIRECTION_LEFT "left"
#define DIRECTION_FORWARD "forward"
#define DIRECTION_RIGHT "right"
#define DIRECTION_BACK "back"

enum class Direction { LEFT,
    UP,
    RIGHT,
    DOWN
};

Direction opposite_direction(Direction direction);
Direction left_direction(Direction direction);
Direction right_direction(Direction direction);
bool is_direction(std::string str);
Direction string_to_direction(std::string str, Direction look_dir);
bool calc_position(size_t old_x, size_t old_y, Direction direction, size_t& new_x, size_t& new_y);
std::string to_string(Direction direction);

#endif