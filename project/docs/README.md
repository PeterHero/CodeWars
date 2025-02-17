## Project Specification and Documentation

## Specification

See project [proposal](proposal.md)

Todo link documentation

## How to compile

This project uses external library loaded using git submodules.
Please download it with
```
git submodule update --init
```

Then to compile use a cmake-aware IDE or locate into `src` directory and build with
```
mkdir build
cd build
cmake ..
cmake --build .
```
