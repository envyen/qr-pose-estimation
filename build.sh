#!/bin/sh

# get directory of script and cd to it
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# no build directory, create it
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# no makefile in build dir, run cmake
if [ ! -f "Makefile" ]; then
  cmake ..
fi

# build it
make -j2
