#!/bin/bash

cd "$CMAKE_ROOT_DIR" || {
    echo -e "${RED}ERROR: Could not change to build directory: $CMAKE_BUILD_DIR${NC}"
    exit 1
}
cd build
./bin/ViRobot
cd -