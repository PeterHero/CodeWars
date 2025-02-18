#include "battle_controller.hpp"
#include <iostream>

Robot::Robot() {}

Robot::Robot(size_t id, size_t pos_x, size_t pos_y, Direction direction)
    : _id(id), _health(ROBOT_MAX_HEALTH), _pos_x(pos_x), _pos_y(pos_y),
      _look_dir(direction) {}

BattleController::BattleController() : _robots_on_field({}) {
  create_robot(1, 0, 0, Direction::RIGHT);
  create_robot(2, 1, 1, Direction::DOWN);
  create_robot(3, 3, 3, Direction::LEFT);
  create_robot(4, 4, 4, Direction::UP);
}

void BattleController::create_robot(size_t id, size_t pos_x, size_t pos_y,
                                    Direction direction) {
  _robots[id] = Robot(id, pos_x, pos_y, direction);
  _robots_on_field[pos_x][pos_y] = id;
}

void BattleController::print_battlefield() {

  for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
    std::cout << "X";
  std::cout << std::endl;

  for (auto row : _robots_on_field) {
    std::cout << "X";
    for (size_t id : row) {
      if (id == ROBOT_NULL_ID) {
        std::cout << " ";
      } else {
        switch (_robots[id]._look_dir) {
        case Direction::LEFT:
          std::cout << "<";
          break;
        case Direction::UP:
          std::cout << "A";
          break;
        case Direction::RIGHT:
          std::cout << ">";
          break;
        case Direction::DOWN:
          std::cout << "V";
          break;
        }
      }
    }
    std::cout << "X" << std::endl;
  }

  for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
    std::cout << "X";
  std::cout << std::endl;
}
