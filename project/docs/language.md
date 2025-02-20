# Robot controlling language

For the purpose of robots controlled by scripts some language should be used.
The straightforward solution is to use custom interpreted language.

## Language features

The language should allow to control flow, get info about the robot and call
robot commands.

### Control flow

- if-else statements
- simple loops

### Info about robot and battlefield

- robot info get-health
- robot info enemy-in-range
- robot info heal-direction

### Robot commands

- robot cmd shoot
- robot cmd move <direction>
- robot cmd turn left/right
