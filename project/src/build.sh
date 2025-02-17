#!/bin/sh
set -eu

git submodule update --init

test -d build || mkdir build
cd build
cmake ..
cmake --build .
