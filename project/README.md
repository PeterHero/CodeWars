# Code Wars

Code wars is a simulation of battle of robots driven by scripts.
You can write your own but there are some example scripts in the example directory.
Have fun testing various strategies. 

## Specification and Documentation

See the docs directory for various files regarding documentation.

[Original idea](docs/proposal.md)

[Game concepts](docs/game-description.md)

[Script language](docs/language.md)

[Design overview](docs/project-design.md)

## Requirements to run

### Hardware requirements

Supported architectures are that supported by the gcc compiler - x86/x86-64, ARM/AArch64, RISC-V,...

### Software requirements

Runs on Windows and Linux. Should also run on OS X but was not tested.

## How to compile

Ensure CMake is installed.

Build by running `./build.sh`

Or run commands manually:

This project uses external library loaded using git submodules.
Please download it with
```
git submodule update --init
```

Then to compile use a cmake-aware IDE or build with
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run

You can use script to run by calling `./run.sh [args]` or directly `./build/code_wars [args]`.

### Usage

You need to provide at least one script file that will be used to control robots.
Then some game parameters can be specified using predefined options:

```
Usage: code_wars [OPTION]... [SCRIPT FILES]...
Code wars simulates fight of robots run by scripts

Options:
-t [number]     set number of teams/robots (default is 10)
-m [mode]       set gamemode to one of [deathmatch/teams/capture] (default is deathmatch)
-s [number]     set game seed (default is random)
-h              print help
```

## Example run