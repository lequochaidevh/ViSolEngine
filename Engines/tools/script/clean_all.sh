#!/bin/bash

. "$(dirname "$0")/lib.sh"
source "$(dirname "$0")/setup_env.sh"

echo -e "${BLUE}${BOLD}🧹 Cleaning all build and install outputs...${NC}"

cd "$(dirname "$0")" || {
    echo -e "${RED}ERROR: Could not locate script directory.${NC}"
    exit 1
}

cd "$CMAKE_ROOT_DIR" || {
    echo -e "${RED}ERROR: Could not change to build directory: $CMAKE_BUILD_DIR${NC}"
    exit 1
}

# Delete CMake cache & files
delete_if_exist "build"
delete_if_exist "../tmp"
delete_if_exist "CMakeCache.txt"
delete_if_exist "CMakeFiles"
delete_if_exist "cmake_install.cmake"
delete_if_exist "Makefile"

echo -e "${GREEN}${BOLD}✅ Clean completed successfully.${NC}"
