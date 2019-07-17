#!/bin/bash

rm -r ./build
mkdir build && cd ./build
cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON
cmake --build .
cd ..
