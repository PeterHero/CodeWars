#include "declarations.hpp"
#include "plog/Log.h"
#include <fstream>
#include <regex>
#include <sstream>

Command::Command(Type cmd_type)
    : type(cmd_type)
{
}
Command::Command(Type cmd_type, Direction direction)
    : type(cmd_type)
    , move_direction(direction)
{
}

Command Command::create_move(const std::string& parameter)
{
    if (parameter == DIRECTION_LEFT) {
        return Command(Type::MOVE, Direction::LEFT);
    } else if (parameter == DIRECTION_UP) {
        return Command(Type::MOVE, Direction ::UP);
    } else if (parameter == DIRECTION_RIGHT) {
        return Command(Type::MOVE, Direction ::RIGHT);
    } else if (parameter == DIRECTION_DOWN) {
        return Command(Type::MOVE, Direction ::DOWN);
    } else {
        return Command(Type::INVALID);
    }
}

Command Command::create_turn(const std::string& parameter)
{
    if (parameter == DIRECTION_LEFT) {
        return Command(Type::TURN_LEFT);
    } else if (parameter == DIRECTION_RIGHT) {
        return Command(Type::TURN_RIGHT);
    } else {
        return Command(Type::INVALID);
    }
}

Interpret::Interpret(const std::string& filename, robot_id_t robot_id,
    std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE>* battlefield,
    std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>* robots_on_field,
    std::map<robot_id_t, Robot>* robots)
    : _current_line(0)
    , _branch_depth(0)
    , _executing(true)
    , _helper(battlefield, robots_on_field, robots)
    , _robot_id(robot_id)

{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
        if (line != "") {
            _script_unsplitted.push_back(line);
            _script.push_back({});
            std::istringstream line_stream(line);
            std::string word;
            while (std::getline(line_stream, word, ' ')) {
                _script.back().push_back(word);
            }
        }
    }
    file.close();
}

bool Interpret::line_is_command()
{
    std::vector<std::string>& line = _script[_current_line];
    return line.size() >= 3 && line[0] == ROBOT_STRING && line[1] == CMD_STRING;
}

bool Interpret::line_evaluate_expr()
{
    if (get_word(1) == TRUE_STRING)
        return true;
    if (get_word(1) == FALSE_STRING)
        return false;

    if (get_word(1) == ROBOT_STRING && get_word(2) == SEES_ENEMY) {
        return _helper.robot_sees_enemy(_robot_id);
    }

    PLOG_ERROR << "invalid expression in if statement";
    return false;
}

size_t Interpret::line_size()
{
    return _script[_current_line].size();
}

std::string& Interpret::get_word(size_t index)
{
    return _script[_current_line][index];
}

Command Interpret::get_command()
{
    std::vector<std::string>& line = _script[_current_line];

    PLOG_VERBOSE << _script_unsplitted[_current_line];

    std::string& cmd_string = get_word(2);

    if (cmd_string == CMD_SHOOT) {
        return Command(Command::Type::SHOOT);
    } else if (cmd_string == CMD_MOVE && line.size() == 4) {
        return Command::create_move(line[3]);
    } else if (cmd_string == CMD_TURN && line.size() == 4) {
        return Command::create_turn(line[3]);
    } else {
        return Command(Command::Type::INVALID);
    }
}

Command Interpret::next_command()
{
    while (!(_executing && line_is_command())) {
        if (get_word(0) == IF_STRING) {
            _branch_depth++;
            if (!line_evaluate_expr()) {
                if (_executing) {
                    current_depth = _branch_depth;
                    _executing = false;
                }
            }
        }

        if (get_word(0) == ELSE_STRING) {
            if (_executing) {
                current_depth = _branch_depth;
                _executing = false;
            } else if (current_depth == _branch_depth) {
                _executing = true;
            }
        }

        if (get_word(0) == ENDIF_STRING) {
            if (current_depth == _branch_depth)
                _executing = true;
            _branch_depth--;
        }

        next_line();
    }

    Command command = get_command();
    next_line();
    return command;
}
