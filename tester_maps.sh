#!/bin/bash

# Color definitions
RED="\x1B[31m"
GRN="\x1B[1;32m"
LGRN="\x1B[32m" # Slightly different shade of green
YEL="\x1B[33m"
BLU="\x1B[34m"
MAG="\x1B[35m"
BMAG="\x1B[1;35m"
CYN="\x1B[36m"
BCYN="\x1B[1;36m"
WHT="\x1B[37m"
RESET="\x1B[0m"
LINEP="\033[75G"

# Executable
exe=./cub3D

# Function to find maps
find_maps() {
    local path=$1
    local exclude_invalid=$2

    if [ "$exclude_invalid" = true ]; then
        find "$path" -type d -name "invalid" -prune -o -type f -name "*.cub" -print
    else
        find "$path" -name "*.cub" | sort
    fi
}

# Function to run a single test
run_test() {
    local map=$1
    local test_type=$2
    local timeout_duration=$3
    local run_valgrind=$4
    local test_number=$5

    local err_msg
    local exit_status

    err_msg=$(timeout --preserve-status "$timeout_duration" "$exe" "$map" 2>&1)
    exit_status=$?

    if [ "$test_type" = "INVALID" ]; then
        if [ $exit_status -ne 0 ]; then
            echo -e "${GRN}${test_number} : ${map}${RESET}"
            echo -e "${GRN}${err_msg}${RESET}"
        else
            echo -e "${RED}${test_number} : ${map}${RESET}"
            echo -e "${RED}DID NOT FAIL${RESET}"
        fi

        if [ "$run_valgrind" = true ]; then
            run_valgrind_check "$map"
        fi
    else
        if [ -z "$err_msg" ]; then
            echo -e "${GRN}${test_number} : ${map} : SUCCESS${RESET}"
        else
            echo -e "${RED}${test_number} : ${map}${RESET}"
            echo -e "${RED}${err_msg}${RESET}"
        fi
    fi
}

# Function to run Valgrind check
run_valgrind_check() {
    local map=$1

    local valgrind_output
    valgrind_output=$(valgrind --leak-check=full --error-exitcode=1 "$exe" "$map" 2>&1)
    if echo "$valgrind_output" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${LGRN}LEAKS OK${RESET}"
    else
        echo -e "${RED}LEAKS DETECTED${RESET}"
    fi
}

# Function to run tests
run_tests() {
    local path=$1
    local test_type=$2
    local exclude_invalid=$3
    local timeout_duration=$4
    local run_valgrind=$5

    local maps
    maps=$(find_maps "$path" "$exclude_invalid")

    echo -e "${BLU}\n\n\t${test_type} TESTER${RESET}"
    local x=0
    IFS=$'\n' read -rd '' -a map_array <<<"$maps"
    for map in "${map_array[@]}"; do
        x=$((x+1))
        run_test "$map" "$test_type" "$timeout_duration" "$run_valgrind" "$x"
    done
}

# Run invalid tests with Valgrind
run_tests "./maps/invalid" "INVALID" false 0.1s true

# Run valid tests without Valgrind
run_tests "./maps" "VALID" true 0.1s false