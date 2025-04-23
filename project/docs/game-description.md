# Game description

The game is played on a field with script controlled robots.
On how the robots are controlled see [language specification](language.md).
There are few different objects and gamemodes.

Run help `code_wars -h` to see options to select number of robots and game mode.

## Game modes

### Deathmatch

Basic game mode, every robot is on its own. The game ends if there is only one
last robot alive or the limit of turns is reached.

### Team deathmatch

Robots are divided into multiple teams competing against each other. The game
ends if there is only one last team alive or the limit of turns is reached.
Be careful, friendly fire is possible!

### Point capture

In this mode there is one more way to win than just killing your oponents. There
are places on the map called points which generate bonus points. If a point is
collected a new one is generated in a few turns. The goal is to gather as many
points as possible but killing your enemies is allowed.

## Game objects

### Robots

Robots have a look direction. Can move, shoot and place bombs.

### Wall

Non-walkable object that stops a bullet.

### Box

Non-walkable object that can be destroyed by a bullet.

### Heal

Walkable object that heals when stepped on.

### Point

In game mode point capture generates points that can be collected. Points are
generated 5 turns after the last collection.

### Bomb

Bomb can be placed on an empty field. It explodes after 3 turns or when hit by
a bullet. On explosion it deals damage to fields in radius 2. It deals twice
the damage of a bullet.
