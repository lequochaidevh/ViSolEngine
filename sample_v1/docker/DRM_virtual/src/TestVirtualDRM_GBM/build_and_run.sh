#!/usr/bin/bash

mkdir build

g++ main.cpp -o ./build/app \
    -lEGL -lGLESv2 -lgbm -ldrm

./build/app