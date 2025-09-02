#!/bin/bash

. "$(dirname "$0")/lib.sh"
source "$(dirname "$0")/setup_env.sh"

# This script builds all components of the ViSolEngine project.
printf "${BLUE}${BOLD}%-10sBuilding all components of the ViSolEngine project.${ENDLINE}${NC}"
echo

cd "$CMAKE_ROOT_DIR" || {
    echo -e "${RED}ERROR: Could not change to build directory: $CMAKE_BUILD_DIR${NC}"
    exit 1
}

# cmake --preset linux-debug
# cmake --preset linux-debug -DCMAKE_INSTALL_PREFIX=./tmp/ViSolEngineInstall
# cmake --build out/build/linux-debug
# cmake --install out/build/linux-debug

mkdir -p ../tmp/ViSolEngineInstall
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../tmp/ViSolEngineInstall"
cmake --build build
cmake --install build

# core_build=$(( $(nproc) - 3 ))
# cmake --build . --preset linux-debug -- -j "$core_build" || {
# # cmake --build . --target all -- -j "$core_build" || {
#     echo -e "${RED}ERROR: Build failed.${NC}"
#     exit 1
# }

# cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./tmp/ViSolEngineInstall
# cmake --build build
# cmake --install build

# mkdir -p ./build
# cmake -S . -B build -G Ninja \
#     -DCMAKE_BUILD_TYPE=Debug \
#     -DCMAKE_INSTALL_PREFIX=./tmp/ViSolEngineInstall

# cmake --build build
# cmake --install build

printf "${GREEN}${BOLD}%-10sBuild completed successfully.${ENDLINE}${NC}"
echo
