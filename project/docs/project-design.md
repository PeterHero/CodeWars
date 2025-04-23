# Project design

Here is a description of the object design and design decisions.

## Object design

Battle controller is the class that controls the game and runs turns.
It calls robots to do an action when on turn.

Robot is a central class which holds most game logic.
To separate concerns an abstraction using interfaces was used on top of Robot class.
Therefore every part of program that interacts with robot cannot access non-desired properties.

Robot calls interpreter class that parses robot's script file and creates next command.
Interpreter receives details about robot using RobotInfo interface.

Command when executed calls an action on robot using RobotActions interface.

When robot interacts with field objects it provides them RobotEvents interface - this way
field objects can modify robot in controlled way.

Field objects have a common interface so that new ones can be simply added if the project be extended.