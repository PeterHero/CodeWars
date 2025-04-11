#include "interpreter.hpp"
#include "commands.hpp"
#include "plog/Log.h"
#include <fstream>
#include <regex>
#include <sstream>

Interpreter::Interpreter(std::string filename, RobotInfo* robot)
    : _robot(robot)
    , _current_line(0)
    , _branch_depth(0)
    , _executing(true)
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

bool Interpreter::line_is_command()
{
    std::vector<std::string>& line = _script[_current_line];
    return line_size() >= 3 && get_word(0) == ROBOT_STRING && get_word(1) == CMD_STRING;
}

bool Interpreter::line_evaluate_expr()
{
    if (get_word(1) == TRUE_STRING)
        return true;
    if (get_word(1) == FALSE_STRING)
        return false;

    if (get_word(1) == ROBOT_STRING && get_word(2) == SEES_ENEMY) {
        return _robot->sees_enemy();
    }

    PLOG_ERROR << "invalid expression in if statement";
    return false;
}

size_t Interpreter::line_size()
{
    return _script[_current_line].size();
}

std::string& Interpreter::get_word(size_t index)
{
    return _script[_current_line][index];
}

std::unique_ptr<Command> Interpreter::get_command()
{
    PLOG_VERBOSE << _script_unsplitted[_current_line];

    std::string& cmd_string = get_word(2);

    if (cmd_string == CMD_SHOOT) {
        return std::make_unique<CommandShoot>();
    } else if (cmd_string == CMD_MOVE && line_size() == 4) {
        if (is_direction(get_word(3)))
            return std::make_unique<CommandMove>(string_to_direction(get_word(3)));
        else
            PLOG_ERROR << get_word(3) << "is not a valid direction";
    } else if (cmd_string == CMD_TURN && line_size() == 4) {
        if (is_rotation(get_word(3)))
            return std::make_unique<CommandTurn>(string_to_rotation(get_word(3)));
        else
            PLOG_ERROR << get_word(3) << "in not a valid rotation";
    } else {
        PLOG_ERROR << "Invalid command!";
        return std::make_unique<CommandMove>(Direction::UP);
    }
}

void Interpreter::next_line()
{
    _current_line = (_current_line + 1) % _script.size();
}

std::unique_ptr<Command> Interpreter::next_command()
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

    auto command = get_command();
    next_line();
    return command;
}