#ifndef robot_hpp_
#define robot_hpp_

#include "direction.hpp"
#include <iostream>

#define ROBOT_MAX_HEALTH 100
#define ROBOT_NULL_ID 0
#define SHOT_DAMAGE 50

using robot_id_t = size_t;

class Robot {
private:
  robot_id_t _id;
  size_t _health;
  size_t _pos_x;
  size_t _pos_y;
  Direction _look_dir;

public:
  Robot();
  Robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction);
  size_t get_x();
  size_t get_y();
  void set_x(size_t new_x);
  void set_y(size_t new_y);
  Direction get_look_dir();
  void turn_left();
  void turn_right();
  void get_shot();
  void heal_to_max();
  bool is_alive();
  void print(std::ostream &stream = std::cout);
};

inline size_t Robot::get_x() { return _pos_x; }
inline size_t Robot::get_y() { return _pos_y; }
inline void Robot::set_x(size_t new_x) { _pos_x = new_x; }
inline void Robot::set_y(size_t new_y) { _pos_y = new_y; }
inline Direction Robot::get_look_dir() { return _look_dir; }

inline void Robot::get_shot() {
  _health = (_health > SHOT_DAMAGE) ? _health - SHOT_DAMAGE : 0;
}

inline void Robot::heal_to_max() { _health = ROBOT_MAX_HEALTH; }
inline bool Robot::is_alive() { return _health > 0; }

std::ostream &operator<<(std::ostream &stream, Robot &robot);

#endif
