#!/bin/sh
set -eu

git submodule update --init

test -d build || mkdir build
cd build

if [ "${1:-NOTSET}" = "-d" ];then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi

cmake --build .
