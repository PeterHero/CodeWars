# Robot controlling language

For the purpose of robots controlled by scripts some language should be used.
The straightforward solution is to use custom interpreted language.
Let it be named robot shell language - *rbsh* (nickname could be 'rubbish').

## How the language is used

The robots are controled using scripts written in *rbsh*. Each robot is assigned
a script from which drives its behaviour during the fight. When robot is on turn
it looks for the next command in the script starting where it finished last time.
The script is therefore run in an infinite loop - first line continues right
after the last one.

## Language features

The language consists of control flow statements and commands. Each statement or
command must be on a separate line. The indentation does not matter.

### Control flow

Control flow statements allow to control which commands are chosen to run.
There are three statements:
- if
- else
- endif

**if** must be followed by an condition and combined with **endif**. If the
condition evaluates to *true* then the commands until **else** or **endif** are
executed. If the condition evaluates to *false* and an **else** statement
follows, then the commands between **else** and **endif** are executed.

Example use - simple if:
```
if {cond}
    {commands}
endif
```

if-else:
```
if {cond}
    {commands}
else
    {commands}
endif
```

if-else statements can be nested (*else-if*):
```
if {cond}
    {commands}
else
    if {cond}
        {commands}
    endif
endif
```

### Conditions

Conditions are used in control flow. They are evaluated to *true* or *false*.
Keywords **true** and **false** can be used as a condition though they are not
particulary useful.

Next follows list of conditions and their description:

`robot see {object}`

Is *true* if there is an *object* in the look direction of the robot.
*Object* can be one of `enemy`, `heal`, `point`, `box`, `bomb`

`robot health {high/low}`

The condition depends whether the current health is above or below 50% health.

`robot can place bomb`

Is *true* if the robot can place a bomb - it has a bomb available and the field
behind the robot is empty.

`robot can move {direction}`

Is *true if the robot can move in a *direction* - one of `forward`, `back`,
`left`, `right`.

### Robot commands

Command is a single action of robot.

`robot cmd shoot`

Robot will shoot in the look direction. The shot will stop with the first object
that is not passable. When the bullet hits:
- robot - the robot hit takes damage
- box - the box is destroyed
- wall - nothing happens
- bomb - the bomb explodes

`robot cmd move {direction}`

Robot moves in the *direction* - one of `forward`, `back`, `left`, `right`.
The robot can move only if there is a walkable object.

`robot cmd turn {left/right}`

Robot turns left or right. It does not move just changes the look direction.

`robot cmd place bomb`

Robot places a bomb behind itself if possible. If the robot is out of bombs or
the field behind the robot is not empty than nothing happens.
