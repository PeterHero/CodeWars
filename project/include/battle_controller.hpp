#ifndef battle_controller_hpp_
#define battle_controller_hpp_

#include <array>
#include <iostream>
#include <map>

#define FIELD_SIZE 5
#define ROBOT_MAX_HEALTH 100
#define ROBOT_NULL_ID 0

using robot_id_t = size_t;

enum class Direction { LEFT, UP, RIGHT, DOWN };

class Robot {
private:
public:
  robot_id_t _id;
  size_t _health;
  size_t _pos_x;
  size_t _pos_y;
  Direction _look_dir;

  Robot();
  Robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction);
  void print(std::ostream &stream = std::cout);
};

std::ostream &operator<<(std::ostream &stream, Robot &robot);

class FieldObject {
public:
  enum class Type { GROUND, WALL };

private:
  Type _type;

public:
  FieldObject();
  FieldObject(Type type);
  bool is_walkable();
  void print(std::ostream &stream = std::cout);
};

std::ostream &operator<<(std::ostream &stream, FieldObject &field_object);

class BattleController {
private:
  std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE> _battlefield;
  std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE> _robots_on_field;
  std::map<robot_id_t, Robot> _robots;

  void create_robot(robot_id_t id, size_t pos_x, size_t pos_y,
                    Direction direction);
  void move_robot(robot_id_t id, Direction direction); // todo

public:
  BattleController();
  void print_battlefield();
};

#endif
