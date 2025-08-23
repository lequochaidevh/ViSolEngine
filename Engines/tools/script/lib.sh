#!/bin/bash

# Export color variables for terminal output
export RED='\033[0;31m'
export GREEN='\033[0;32m'
export YELLOW='\033[0;33m'
export BLUE='\033[0;34m'
export PURPLE='\033[0;35m'
export CYAN='\033[0;36m'
export NC='\033[0m' # No Color
export BOLD='\033[1m'
export UNDERLINE='\033[4m'
export ENDLINE='\033[0m'


printf_var() {
    local var_name="$1"
    local var_value="${!var_name}"
    if [ -z "$var_value" ]; then
        echo -e "${YELLOW}WARNING: Variable '$var_name' is not set.${NC}"
    else
        printf "${GREEN}${BOLD}%-50s${CYAN}${BOLD}%s${ENDLINE}${NC}\n" "$var_name" "$var_value"
    fi
}

delete_if_exist() {
    local file_name="$1"
    if [ -e "$file_name" ]; then
        echo "$file_name exist. Remove it ..."
        rm -rf $file_name
    fi
}

# TODO:
# create_if_not_exist()