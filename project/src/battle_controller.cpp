#include "battle_controller.hpp"
#include <iostream>

Robot::Robot() {}

Robot::Robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction)
    : _id(id), _health(ROBOT_MAX_HEALTH), _pos_x(pos_x), _pos_y(pos_y),
      _look_dir(direction) {}

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
  default:
    return false;
  }
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
  create_robot(2, 1, 1, Direction::DOWN);
  create_robot(3, 3, 3, Direction::LEFT);
  create_robot(4, 4, 4, Direction::UP);
}

void BattleController::create_robot(robot_id_t id, size_t pos_x, size_t pos_y,
                                    Direction direction) {
  _robots[id] = Robot(id, pos_x, pos_y, direction);
  _robots_on_field[pos_x][pos_y] = id;
}

void BattleController::print_battlefield() {
  for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
    std::cout << "X";
  std::cout << std::endl;

  for (size_t i = 0; i < FIELD_SIZE; ++i) {
    std::cout << "X";
    for (size_t j = 0; j < FIELD_SIZE; ++j) {
      robot_id_t robot_id = _robots_on_field[i][j];
      if (robot_id == ROBOT_NULL_ID) {
        std::cout << _battlefield[i][j];
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
