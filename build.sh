#!/bin/bash

rm -r ./build
mkdir build && cd ./build
cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Debug -DTMXL_BUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build .
cd ..
