#include "interpreter.hpp"
#include "command_factory.hpp"
#include "commands.hpp"
#include "expressions.hpp"
#include "field_objects.hpp"
#include "plog/Log.h"
#include <fstream>
#include <regex>
#include <sstream>

/**
 * @brief Construct a new Interpreter:: Interpreter object - save script text to memory
 *
 * @param filename
 */
Interpreter::Interpreter(std::string filename)
    : _current_line(0)
    , _branch_depth(0)
    , _executing(true)
    , _filename(filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
        if (line != "") {
            _script_unsplitted.push_back(line);
            std::vector<std::string> words;
            std::istringstream line_stream(line);
            std::string word;
            while (line_stream >> word) {
                words.push_back(word);
            }
            _script.push_back(words);
        }
    }
    file.close();
}

/**
 * @brief Checks if current line is a command
 *
 * @return true
 * @return false
 */
bool Interpreter::line_is_command()
{
    std::vector<std::string>& line = _script[_current_line];
    return line_size() >= 3 && get_word(0) == ROBOT_STRING && get_word(1) == CMD_STRING;
}

/**
 * @brief Evaluates an expression in current line
 *
 * @param robot Provided info about robot
 * @return true If expression evaluates to true
 * @return false otherwise
 */
bool Interpreter::line_evaluate_expr(RobotInfo& robot)
{
    std::unique_ptr<Expression> expr = std::make_unique<GeneralExpression>();
    auto begin = ++_script[_current_line].begin();
    auto end = _script[_current_line].end();
    return expr->evaluate(begin, end, robot);
}

/**
 * @brief Return current line size
 *
 * @return size_t
 */
size_t Interpreter::line_size()
{
    return _script[_current_line].size();
}

/**
 * @brief Get n-th word from current line
 *
 * @param index index of word in line
 * @return std::string& the word
 */
std::string& Interpreter::get_word(size_t index)
{
    if (index <= line_size())
        return _script[_current_line][index];
    else {
        PLOG_ERROR << "invalid index";
        std::abort();
    }
}

/**
 * @brief Factory method to create new command from line is form of command
 *
 * @param robot info about robot
 * @return std::unique_ptr<Command> new command
 */
std::unique_ptr<Command> Interpreter::get_command(RobotInfo& robot)
{
    PLOG_VERBOSE << _script_unsplitted[_current_line];
    return CommandFactory::create(_script[_current_line], robot);
}

/**
 * @brief Set current line to next
 *
 */
void Interpreter::next_line()
{
    _current_line = (_current_line + 1) % _script.size();
}

/**
 * @brief Parse script until next command and return it
 *
 * @param robot robot info
 * @return std::unique_ptr<Command> Next command
 */
std::unique_ptr<Command> Interpreter::next_command(RobotInfo& robot)
{
    while (!(_executing && line_is_command())) {
        if (get_word(0) == IF_STRING) {
            _branch_depth++;
            if (_executing && !line_evaluate_expr(robot)) {
                current_depth = _branch_depth;
                _executing = false;
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

    auto command = get_command(robot);
    next_line();
    return std::move(command);
}