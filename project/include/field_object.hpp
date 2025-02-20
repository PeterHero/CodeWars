#ifndef field_object_hpp_
#define field_object_hpp_

#include <iostream>

class FieldObject {
public:
  enum class Type { GROUND, WALL };

private:
  Type _type;

public:
  FieldObject();
  FieldObject(Type type);
  bool is_walkable();
  bool is_bullet_passable();
  void print(std::ostream &stream = std::cout);
};

std::ostream &operator<<(std::ostream &stream, FieldObject &field_object);

#endif
