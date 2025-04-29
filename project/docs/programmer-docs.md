# Programmer documentation

## Used libraries

Plog - logging library - is the only library used. It has 3 purposes:
1. Log info about script parsing (printing next command)
2. Log robot actions and interaction with battlefield and each other
3. Log parse errors when interpreting the script file

## Classes description

Here is the description of main interfaces and classes used in the program.
Also see [uml diagram](classes.png).

### Battle Controller

```
class BattleController {
public:
    void setup_robots(std::vector<std::string>& scripts, size_t number_of_teams, size_t robots_in_team);
    void setup_battlefield();
    void simulate_battle();
};
```

Battle controller is responsible for creating battlefield with robots and objects and for running the simulation.
It has functions to prepare internal data for battle simulation - `setup_robot()`, `setup_battlefield()`.
Then there is the main game function `simulate_battle()`. There each turn robots are called to do an action.

### Robot

Robot is a class that implements interfaces: Character, RobotActions, RobotEvents and RobotInfo.
This is a central class responsible for most of the game logic. It is accesible from other classes using
several interfaces so that only needed functions of robot can be accessed.

In `act()` Robot calls interpreter class that parses robot's script file and creates next command.

### Character

```
class Character {
public:
    virtual void act() = 0;
    virtual bool is_alive() = 0;
    virtual robot_id_t id() = 0;
    virtual size_t team_id() = 0;
    virtual size_t points() = 0;
    virtual std::string script_file() = 0;
};
```

Character is a living object that takes active part of the game.
Method `act()` is what drives the character behaviour.

### Robot Actions

```
class RobotActions {
public:
    virtual void shoot() = 0;
    virtual void move(Direction direction) = 0;
    virtual void turn(Rotation rotation) = 0;
    virtual void place_bomb() = 0;
};
```

This interface describes actions that a robot can do.
Individual actions are described in the [language description](language.md).

### Robot Events

```
class RobotEvents {
public:
    virtual void heal() = 0;
    virtual void take_damage(size_t damage) = 0;
    virtual void collect_point() = 0;
    virtual void explode_bomb() = 0;
};
```

This interface describes events that can happen to Robot. Usually they happen in interaction with Field Objects.

### Robot Info

```
class RobotInfo {
public:
    virtual bool sees_enemy() = 0;
    virtual bool sees(std::string object_string) = 0;
    virtual bool can_move(Direction direction) = 0;
    virtual bool can_place_bomb() = 0;
    virtual bool is_low_health() = 0;
    virtual Direction look_direction() = 0;
};
```

This interfaces provides access to information about robot and battlefield.
Individual methods are tied to conditions described in the [language description](language.md).

### Interpreter

```
class Interpreter {
public:
    std::unique_ptr<Command> next_command(RobotInfo& robot);
};
```

Interpreter class parses a script file. The `next_command()` function parses creates a new Command described in the script file.

### Command

```
class Command {
public:
    virtual void execute(RobotActions& robot) = 0;
};
```

Command class holds an action that will be called on robot in the `execute()` method.

### Field Object

```
class FieldObject {
public:
    virtual std::string get_type() = 0;
    virtual bool is_walkable() = 0;
    virtual bool is_bullet_passable() = 0;
    virtual bool is_empty() = 0;
    virtual void on_step_action(RobotEvents& robot) = 0;
    virtual std::unique_ptr<FieldObject> on_shoot_action(std::unique_ptr<FieldObject> previous) = 0;
    virtual void print() = 0;
    virtual void turn_refresh() = 0;
};
```

This interface defines a field object that is placed on the battlefield. Methods define how other objects interface with it (if it can be walked on etc.).
When stepped on it calls an event on robot.
