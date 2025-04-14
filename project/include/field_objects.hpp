#ifndef field_objects_hpp_
#define field_objects_hpp_

#include "field_object.hpp"

class Ground : public FieldObject {
public:
    std::string get_type() override { return "ground"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return true; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
};

class Wall : public FieldObject {
public:
    std::string get_type() override { return "wall"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
};

class Box : public FieldObject {
public:
    std::string get_type() override { return "box"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::make_unique<Ground>(); }
};

class Heal : public FieldObject {
public:
    std::string get_type() override { return "heal"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { robot.heal(); }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
};

class Point : public FieldObject {
public:
    std::string get_type() override { return "point"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { robot.collect_point(); }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
};

class Bomb : public FieldObject {
    // todo implement damaging
    // pass battlefield pointers
public:
    std::string get_type() override { return "bomb"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::make_unique<Ground>(); }
};

#endif
