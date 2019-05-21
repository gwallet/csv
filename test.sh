#!/bin/sh

if [ ! -d build ]; then
  mkdir build
  cd build
  cmake ..
else
  cd build
fi

cmake --build .
env CTEST_OUTPUT_ON_FAILURE=1 make test
