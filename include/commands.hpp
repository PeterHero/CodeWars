#ifndef commands_hpp_
#define commands_hpp_

#include "command.hpp"

class CommandShoot : public Command {
public:
    void execute(RobotActions& robot) override
    {
        robot.shoot();
    }
};

class CommandMove : public Command {
private:
    Direction _direction;

public:
    CommandMove(Direction direction)
        : _direction(direction)
    {
    }

    void execute(RobotActions& robot) override
    {
        robot.move(_direction);
    }
};

class CommandTurn : public Command {
private:
    Rotation _rotation;

public:
    CommandTurn(Rotation rotation)
        : _rotation(rotation)
    {
    }

    void execute(RobotActions& robot) override
    {
        robot.turn(_rotation);
    }
};

class CommandPlaceBomb : public Command {
public:
    void execute(RobotActions& robot) override
    {
        robot.place_bomb();
    }
};

#endif
