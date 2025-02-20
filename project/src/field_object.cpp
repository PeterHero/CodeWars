#include "field_object.hpp"

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
