#include "battle_controller.hpp"

Robot::Robot(size_t pos_x, size_t pos_y)
    : _health(ROBOT_MAX_HEALTH), _pos_x(pos_x), _pos_y(pos_y) {}

BattleController::BattleController() { _robots.push_back(Robot(0, 0)); }

void BattleController::create_robot(size_t pos_x, size_t pos_y) {
  Robot new_robot(pos_x, pos_y);
  _robots.push_back(new_robot);
  _robots_on_field.at(pos_x).at(pos_y);
  _robots_on_field[pos_x][pos_y] = &new_robot;
  // this may be bad if pointer changes, due to reallocation in vector?
}

void BattleController::print_battlefield() {}
