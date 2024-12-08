## Project specification

### Code wars

Program simulates a fight of robots, that are run by user-written code.
It will consist of 2 parts: fight simulation and simple language interpreter.
Robots will fight on a 2d battlefield and features different game modes
e.g. deathmatch, team deathmatch, point capture.
The core of the fight is movement and simple shooting, but other features
are possible e.g. grenades, placing bombs, traps, boosts, healing points etc.

The language for controlling a robot should implement commands such as
move left or shoot, conditions and predefined functions e.g. enemy_in_range.

Application will use a logging library Plog for logging events during the simulation
and errors in interpreted language.

There will be an option to print the battlefield after every turn.
