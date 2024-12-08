## Project Specification and Documentation

Put your project proposal in this folder and create a link from this [README](README.md).

Do the same with project documentation later.

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

