#ifndef field_object_hpp_
#define field_object_hpp_

#include <iostream>

class Robot;

class FieldObject {
public:
    enum class Type { GROUND,
        WALL,
        HEAL };

private:
    Type _type;

public:
    FieldObject();
    FieldObject(Type type);
    bool is_walkable();
    bool is_bullet_passable();
    bool on_step_action(Robot& robot);
    std::string get_action_message();
    void print(std::ostream& stream = std::cout);
};

std::ostream& operator<<(std::ostream& stream, FieldObject& field_object);

#endif
