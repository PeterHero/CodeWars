#ifndef battle_controller_hpp_
#define battle_controller_hpp_

#include <array>
#include <vector>

#define FIELD_SIZE 5
#define ROBOT_MAX_HEALTH 100

class Robot {
private:
  size_t _health;
  size_t _pos_x;
  size_t _pos_y;

public:
  Robot(size_t pos_x, size_t pos_y);
};

class BattleController {
private:
  std::array<std::array<Robot *, 5>, 5> _robots_on_field;
  std::vector<Robot> _robots;

  void create_robot(size_t pos_x, size_t pos_y);

public:
  BattleController();
  void print_battlefield();
};

#endif
