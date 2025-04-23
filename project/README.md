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
