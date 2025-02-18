#ifndef battle_controller_hpp_
#define battle_controller_hpp_

#include <array>
#include <map>

#define FIELD_SIZE 5
#define ROBOT_MAX_HEALTH 100
#define ROBOT_NULL_ID 0

enum class Direction { LEFT, UP, RIGHT, DOWN };

class Robot {
private:
public:
  size_t _id;
  size_t _health;
  size_t _pos_x;
  size_t _pos_y;
  Direction _look_dir;

  Robot();
  Robot(size_t id, size_t pos_x, size_t pos_y, Direction direction);
};

class BattleController {
private:
  std::array<std::array<size_t, FIELD_SIZE>, FIELD_SIZE> _robots_on_field;
  std::map<size_t, Robot> _robots;

  void create_robot(size_t id, size_t pos_x, size_t pos_y, Direction direction);

public:
  BattleController();
  void print_battlefield();
};

#endif
