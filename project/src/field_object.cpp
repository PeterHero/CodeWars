#include "field_object.hpp"

FieldObject::FieldObject()
    : _type(Type::GROUND)
{
}

FieldObject::FieldObject(Type type)
    : _type(type)
{
}

bool FieldObject::is_walkable()
{
    switch (_type) {
    case Type::GROUND:
        return true;
    case Type::WALL:
        return false;
    case Type::HEAL:
        return true;
    }

    return false;
}

bool FieldObject::is_bullet_passable()
{
    switch (_type) {
    case Type::GROUND:
        return true;
    case Type::WALL:
        return false;
    case Type::HEAL:
        return true;
    }

    return false;
}

bool FieldObject::on_step_action(Robot& robot)
{
    switch (_type) {
    case Type::HEAL:
        robot.heal_to_max();
        return true;
    default:
        return false;
    }
}

std::string FieldObject::get_action_message()
{
    switch (_type) {
    case Type::HEAL:
        return "stepped on a heal and got healed to max health";
    default:
        return "";
    }
}

void FieldObject::print(std::ostream& stream)
{
    switch (_type) {
    case Type::GROUND:
        stream << " ";
        break;
    case Type::WALL:
        stream << "W";
        break;
    case Type::HEAL:
        stream << "H";
        break;
    }
}

std::ostream& operator<<(std::ostream& stream, FieldObject& field_object)
{
    field_object.print(stream);
    return stream;
}
