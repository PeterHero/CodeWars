#ifndef field_objects_hpp_
#define field_objects_hpp_

#include "field_object.hpp"
#include <iostream>
#include <plog/Log.h>

#define BOMB_TURNS 3
#define POINT_TURNS 2

class Ground : public FieldObject {
public:
    std::string get_type() override { return "ground"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return true; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
    void print() override { std::cout << " "; }
    void turn_refresh() override { };
};

class Wall : public FieldObject {
public:
    std::string get_type() override { return "wall"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
    void print() override { std::cout << "W"; }
    void turn_refresh() override { };
};

class Box : public FieldObject {
public:
    std::string get_type() override { return "box"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::make_unique<Ground>(); }
    void print() override { std::cout << "O"; }
    void turn_refresh() override { };
};

class Heal : public FieldObject {
public:
    std::string get_type() override { return "heal"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { robot.heal(); }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
    void print() override { std::cout << "H"; }
    void turn_refresh() override { };
};

class Point : public FieldObject {
private:
    size_t turns_till_active = 0;

public:
    std::string get_type() override { return "point"; }
    bool is_walkable() override { return true; }
    bool is_bullet_passable() override { return true; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override
    {
        if (turns_till_active == 0) {
            robot.collect_point();
            turns_till_active = POINT_TURNS;
        }
    }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override { return std::move(previous); }
    void print() override { std::cout << ((turns_till_active == 0) ? "P" : "p"); }
    void turn_refresh() override
    {
        if (turns_till_active > 0)
            turns_till_active--;
    };
};

class Bomb : public FieldObject {
    int turns = BOMB_TURNS;
    RobotEvents* _owner;

    void explode()
    {
        _owner->explode_bomb();
    }

public:
    size_t pos_x;
    size_t pos_y;

    Bomb(RobotEvents* owner, size_t x, size_t y)
        : _owner(owner)
        , pos_x(x)
        , pos_y(y)
    {
    }

    void tick()
    {
        turns--;
        PLOG_WARNING << "Bomb ticks... " << turns << " turns left!";
        if (turns == 0) {
            explode();
        }
    }

    std::string get_type() override { return "bomb"; }
    bool is_walkable() override { return false; }
    bool is_bullet_passable() override { return false; }
    bool is_empty() override { return false; }
    void on_step_action(RobotEvents& robot) override { }
    std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) override
    {
        explode();
        return std::make_unique<Ground>();
    }
    void print() override { std::cout << "B"; }
    void turn_refresh() override { };
};

inline bool is_object(std::string str)
{
    return str == Ground {}.get_type()
        || str == Wall {}.get_type()
        || str == Box {}.get_type()
        || str == Heal {}.get_type()
        || str == Point {}.get_type()
        || str == Bomb { 0, 0, 0 }.get_type();
}

#endif
