#include "battle_controller.hpp"
#include <iostream>
#include <plog/Log.h>

std::string to_string(Direction &direction) {
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

bool calc_position(size_t old_x, size_t old_y, Direction direction,
                   size_t &new_x, size_t &new_y) {
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

Robot::Robot() {}

Robot::Robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction)
    : _id(id), _health(ROBOT_MAX_HEALTH), _pos_x(pos_x), _pos_y(pos_y),
      _look_dir(direction) {}

void Robot::turn_left() {
  switch (_look_dir) {
  case Direction::LEFT:
    _look_dir = Direction::DOWN;
    break;
  case Direction::UP:
    _look_dir = Direction::LEFT;
    break;
  case Direction::RIGHT:
    _look_dir = Direction::UP;
    break;
  case Direction::DOWN:
    _look_dir = Direction::RIGHT;
    break;
  }
}

void Robot::turn_right() {
  switch (_look_dir) {
  case Direction::LEFT:
    _look_dir = Direction::UP;
    break;
  case Direction::UP:
    _look_dir = Direction::RIGHT;
    break;
  case Direction::RIGHT:
    _look_dir = Direction::DOWN;
    break;
  case Direction::DOWN:
    _look_dir = Direction::LEFT;
    break;
  }
}

bool Robot::get_shot() {
  _health = (_health > SHOT_DAMAGE) ? _health - SHOT_DAMAGE : 0;
  return _health == 0;
}

void Robot::print(std::ostream &stream) {
  switch (_look_dir) {
  case Direction::LEFT:
    stream << "<";
    break;
  case Direction::UP:
    stream << "A";
    break;
  case Direction::RIGHT:
    stream << ">";
    break;
  case Direction::DOWN:
    stream << "V";
    break;
  }
}

std::ostream &operator<<(std::ostream &stream, Robot &robot) {
  robot.print(stream);
  return stream;
}

FieldObject::FieldObject() : _type(Type::GROUND) {}

FieldObject::FieldObject(Type type) : _type(type) {}

bool FieldObject::is_walkable() {
  switch (_type) {
  case Type::GROUND:
    return true;
  case Type::WALL:
    return false;
  }

  return false;
}

bool FieldObject::is_bullet_passable() {
  switch (_type) {
  case Type::GROUND:
    return true;
  case Type::WALL:
    return false;
  }

  return false;
}

void FieldObject::print(std::ostream &stream) {
  switch (_type) {
  case Type::GROUND:
    stream << " ";
    break;
  case Type::WALL:
    stream << "W";
    break;
  }
}

std::ostream &operator<<(std::ostream &stream, FieldObject &field_object) {
  field_object.print(stream);
  return stream;
}

BattleController::BattleController() : _robots_on_field({}), _battlefield({}) {
  _battlefield[0][1] = FieldObject(FieldObject::Type::WALL);

  create_robot(1, 0, 0, Direction::RIGHT);
  create_robot(2, 1, 1, Direction::RIGHT);
  create_robot(3, 3, 3, Direction::LEFT);
  create_robot(4, 4, 4, Direction::LEFT);

  print_battlefield();
  robot_shoot(1);
  robot_move(1, Direction::RIGHT);
  robot_shoot(1);
  robot_shoot(1);
  _robots[1].turn_left();
  _robots[3].turn_left();
  print_battlefield();
}

void BattleController::create_robot(robot_id_t id, size_t pos_x, size_t pos_y,
                                    Direction direction) {
  _robots[id] = Robot(id, pos_x, pos_y, direction);
  _robots_on_field[pos_x][pos_y] = id;
}

void BattleController::robot_move(robot_id_t id, Direction direction) {
  Robot robot = _robots[id];
  size_t new_x;
  size_t new_y;
  if (calc_position(robot._pos_x, robot._pos_y, direction, new_x, new_y)) {
    if (_robots_on_field[new_x][new_y] == ROBOT_NULL_ID &&
        _battlefield[new_x][new_y].is_walkable()) {
      _robots_on_field[robot._pos_x][robot._pos_y] = ROBOT_NULL_ID;
      _robots_on_field[new_x][new_y] = id;
      robot._pos_x = new_x;
      robot._pos_y = new_y;
      PLOG_INFO << "Robot " << id << " moved " << to_string(direction);
    }
  }
}

void BattleController::robot_shoot(robot_id_t id) {
  // todo debug this
  // and learn to debug in vs code
  Robot robot = _robots[id];
  size_t bullet_x = robot._pos_x;
  size_t bullet_y = robot._pos_y;
  while (
      calc_position(bullet_x, bullet_y, robot._look_dir, bullet_x, bullet_y)) {
    std::cout << "x: " << bullet_x << " y: " << bullet_y << std::endl;
    robot_id_t target_id = _robots_on_field[bullet_x][bullet_y];
    if (target_id != ROBOT_NULL_ID) {
      if (_robots[target_id].get_shot())
        PLOG_ERROR << "Robot " << id << " killed robot " << target_id;
      else
        PLOG_WARNING << "Robot " << id << " shot robot " << target_id;
      break;
    } else if (!_battlefield[bullet_x][bullet_y].is_bullet_passable()) {
      break;
    }
  }
}

void BattleController::print_battlefield() {
  for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
    std::cout << "X";
  std::cout << std::endl;

  for (size_t i = 0; i < FIELD_SIZE; ++i) {
    size_t y = FIELD_SIZE - 1 - i;
    std::cout << "X";
    for (size_t x = 0; x < FIELD_SIZE; ++x) {
      robot_id_t robot_id = _robots_on_field[x][y];
      if (robot_id == ROBOT_NULL_ID) {
        std::cout << _battlefield[x][y];
      } else {
        std::cout << _robots[robot_id];
      }
    }
    std::cout << "X" << std::endl;
  }

  for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
    std::cout << "X";
  std::cout << std::endl;
}
