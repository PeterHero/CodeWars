#ifndef expressions_hpp_
#define expressions_hpp_

#include "field_objects.hpp"
#include "plog/Log.h"
#include "robot_info.hpp"
#include <string>
#include <vector>

class Expression {
public:
    virtual bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        = 0;
    virtual ~Expression() = default;
};

class TrueExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return true;
    }
};

class FalseExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return false;
    }
};

class SeeEnemyExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return robot.sees_enemy();
    }
};

class SeeObjectExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        auto object = *begin;
        return robot.sees(object);
    }
};

class SeeExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty see expression";
            return false;
        }

        auto word = *begin;
        if (word == "enemy")
            return SeeEnemyExpression().evaluate(++begin, end, robot);
        else if (is_object(word))
            return SeeObjectExpression().evaluate(begin, end, robot);
        else {
            PLOG_ERROR << "Unknown object";
            return false;
        }
    }
};

class HealthHighExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return !robot.is_low_health();
    }
};

class HealthLowExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return robot.is_low_health();
    }
};

class HealthExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty health expression";
            return false;
        }

        auto word = *begin;
        if (word == "high")
            return HealthHighExpression().evaluate(++begin, end, robot);
        else if (word == "low")
            return HealthLowExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown health expression";
            return false;
        }
    }
};

class CanPlaceBombExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        return robot.can_place_bomb();
    }
};

class CanPlaceExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty can place expression";
            return false;
        }

        auto word = *begin;
        if (word == "bomb")
            return CanPlaceBombExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown can place expression";
            return false;
        }
    }
};

class CanMoveDirectionExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        auto word = *begin;
        return robot.can_move(string_to_direction(word, robot.look_direction()));
    }
};

class CanMoveExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty can move expression";
            return false;
        }

        auto word = *begin;
        if (is_direction(word))
            return CanMoveDirectionExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown can move expression";
            return false;
        }
    }
};

class CanExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty can expression";
            return false;
        }

        auto word = *begin;
        if (word == "place")
            return CanPlaceExpression().evaluate(++begin, end, robot);
        else if (word == "move")
            return CanMoveExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown can expression";
            return false;
        }
    }
};

class RobotExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty robot expression";
            return false;
        }

        auto word = *begin;
        if (word == "see")
            return SeeExpression().evaluate(++begin, end, robot);
        else if (word == "health")
            return HealthExpression().evaluate(++begin, end, robot);
        else if (word == "can")
            return CanExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown robot expression";
            return false;
        }
    }
};

class GeneralExpression : public Expression {
public:
    bool evaluate(
        std::vector<std::string>::const_iterator begin,
        std::vector<std::string>::const_iterator end,
        RobotInfo& robot)
        override
    {
        if (begin == end) {
            PLOG_ERROR << "Empty expression";
            return false;
        }

        auto word = *begin;
        if (word == "true")
            return TrueExpression().evaluate(++begin, end, robot);
        else if (word == "false")
            return FalseExpression().evaluate(++begin, end, robot);
        else if (word == "robot")
            return RobotExpression().evaluate(++begin, end, robot);
        else {
            PLOG_ERROR << "Unknown expression";
            return false;
        }
    }
};

#endif