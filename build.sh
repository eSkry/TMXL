#!/bin/bash

rm -r ./build
mkdir build && cd ./build
conan install .. --build=missing
cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON -DBUILD_TMXL_TEST_ONLY=OFF
cmake --build .
cd ..
