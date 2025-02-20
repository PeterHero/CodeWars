#ifndef battle_controller_hpp_
#define battle_controller_hpp_

#include "direction.hpp"
#include "field_object.hpp"
#include "robot.hpp"
#include <array>
#include <map>

class BattleController {
private:
  std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE> _battlefield;
  std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE> _robots_on_field;
  std::map<robot_id_t, Robot> _robots;

  void create_robot(robot_id_t id, size_t pos_x, size_t pos_y,
                    Direction direction);
  void robot_move(robot_id_t id, Direction direction);
  void robot_shoot(robot_id_t id);
  void robot_turn_left(robot_id_t id);
  void robot_turn_right(robot_id_t id);
  void print_battlefield();

public:
  BattleController();
};

#endif
