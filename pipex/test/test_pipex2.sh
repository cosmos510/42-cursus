#!/bin/bash

# Colors for output
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

# Test files
INFILE="./files/infile"
OUTFILE_PIPEX="outfile_pipex"
VALGRIND_LOG="valgrind.log"

# Function to display usage
display_usage() {
    echo "Usage: $0 [test_type]"
    echo "Available test types:"
    echo "  all        - Run all tests with Valgrind (default)"
    echo "  two        - Run two-command tests with Valgrind"
    echo "  multi      - Run multi-command tests with Valgrind"
    echo "  error      - Run error case tests with Valgrind"
    echo "  help       - Display this help message"
}

# Check if input file exists
if [ ! -f "$INFILE" ]; then
    echo -e "${RED}Error:${RESET} Test file '$INFILE' not found."
    exit 1
fi

# Function to run a Valgrind test
run_valgrind_test() {
    local infile=$1
    local commands=("$@")
    local outfile=$OUTFILE_PIPEX
    local num_commands=${#commands[@]}

    # Construct Pipex command
    local pipex_cmd="./pipex "
    for cmd in "${commands[@]}"; do
        pipex_cmd+=" \"$cmd\""
    done
    pipex_cmd+=" $outfile"

    # Display the test
    echo -e "${BLUE}Running Valgrind command:${RESET} $pipex_cmd"

    # Run the command under Valgrind
    valgrind --leak-check=full --trace-children=yes --log-file="$VALGRIND_LOG" $pipex_cmd > /dev/null 2>&1

    # Check Valgrind output
    if grep -q "All heap blocks were freed -- no leaks are possible" "$VALGRIND_LOG"; then
        echo -e "${GREEN}✓ No memory leaks detected${RESET}"
    else
        echo -e "${RED}✗ Memory leaks detected!${RESET}"
        cat "$VALGRIND_LOG"
    fi
    echo "----------------------"
}

# Two-command tests
run_two_tests() {
    echo "Running two-command tests with Valgrind..."
    run_valgrind_test "$INFILE" "cat" "wc -l"
    run_valgrind_test "$INFILE" "grep test" "wc -w"
    run_valgrind_test "$INFILE" "cat" "sort"
    run_valgrind_test "$INFILE" "tr 'a-z' 'A-Z'" "wc -c"
    run_valgrind_test "$INFILE" "grep -v error" "wc -l"
    run_valgrind_test "$INFILE" "sed 's/test/TEST/g'" "wc -l"
    run_valgrind_test "$INFILE" "awk '{print \$1}'" "sort"
    run_valgrind_test "$INFILE" "rev" "wc -l"
    run_valgrind_test "$INFILE" "tail -n 5" "wc -l"
    run_valgrind_test "$INFILE" "head -n 3" "grep test"
    run_valgrind_test "$INFILE" "grep test" "awk '{print \$1}'"
    run_valgrind_test "$INFILE" "ls -la" "grep '^d'"
}

# Multi-command tests
run_multi_tests() {
    echo "Running multi-command tests with Valgrind..."
    run_valgrind_test "$INFILE" "cat" "grep test" "wc -l"
    run_valgrind_test "$INFILE" "cat" "sort" "uniq" "wc -l"
    run_valgrind_test "$INFILE" "grep test" "cut -c1-5" "sort" "uniq"
}

# Error case tests
run_error_tests() {
    echo "Running error case tests with Valgrind..."
    run_valgrind_test "nonexistent_file" "cat" "wc -l"
    run_valgrind_test "$INFILE" "invalid_command" "wc -l"
}

# Main entry point
TEST_TYPE=${1:-"all"}

echo "Starting Pipex Valgrind tests..."
echo "======================"

case "$TEST_TYPE" in
    "all")
        run_two_tests
        run_multi_tests
        run_error_tests
        ;;
    "two")
        run_two_tests
        ;;
    "multi")
        run_multi_tests
        ;;
    "error")
        run_error_tests
        ;;
    "help"|"-h"|"--help")
        display_usage
        exit 0
        ;;
    *)
        echo "Unknown test type: $TEST_TYPE"
        display_usage
        exit 1
        ;;
esac

echo "======================"
echo "All Valgrind tests completed."
