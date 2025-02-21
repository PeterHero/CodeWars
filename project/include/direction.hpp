#ifndef direction_hpp_
#define direction_hpp_

#include <string>

#define FIELD_SIZE 5
#define DIRECTION_LEFT "left"
#define DIRECTION_UP "up"
#define DIRECTION_RIGHT "right"
#define DIRECTION_DOWN "down"

enum class Direction { LEFT, UP, RIGHT, DOWN };

std::string to_string(Direction &direction);

bool calc_position(size_t old_x, size_t old_y, Direction direction,
                   size_t &new_x, size_t &new_y);

#endif
