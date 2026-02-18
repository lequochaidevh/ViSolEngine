#!/usr/bin/bash


mkdir build

g++ main.cpp -o ./build/app -lEGL -lGLESv2

./build/app

# HOST
# xdg-open output.ppm
