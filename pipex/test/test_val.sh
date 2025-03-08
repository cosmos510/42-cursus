#!/bin/bash

# Colors for output
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

# Test files
INFILE="./files/infile"
OUTFILE_BASH="outfile_bash"
OUTFILE_PIPEX="outfile_pipex"
VALGRIND_LOG="valgrind.log"

# Default: no Valgrind
VALGRIND_MODE=false

# Function to display usage
display_usage() {
    echo "Usage: $0 [test_type] [--valgrind]"
    echo "Available test types:"
    echo "  all        - Run all tests (default)"
    echo "  cat        - Run cat related tests"
    echo "  grep       - Run grep related tests"
    echo "  ...        - Other test types as defined"
    echo "Options:"
    echo "  --valgrind - Run Valgrind memory checks during tests"
}

# Check if test files exist
if [ ! -f "$INFILE" ]; then
    echo -e "${RED}Error:${RESET} Test file '$INFILE' not found."
    exit 1
fi

# Parse arguments
TEST_TYPE=${1:-"all"}
if [[ "$2" == "--valgrind" ]]; then
    VALGRIND_MODE=true
fi

# Function to run tests for a specific type
run_test_type() {
    local test_type=$1
    
    case $test_type in
        # Test cases (examples only, add all as in your script)
        "cat")
            COMMANDS=("cat|wc -l" "cat|wc -w")
            ;;
        "multi")
            COMMANDS=("cat|grep test|wc -l" "cat|sort|uniq|wc -l")
            ;;
        *)
            echo "Unknown test type: $test_type"
            return 1
            ;;
    esac

    echo "Running $test_type tests..."
    for test_case in "${COMMANDS[@]}"; do
        CMD1=$(echo "$test_case" | cut -d'|' -f1)
        CMD2=$(echo "$test_case" | cut -d'|' -f2)
        
        echo -e "${BLUE}Bash command:${RESET} < $INFILE $CMD1 | $CMD2 > $OUTFILE_BASH"
        echo -e "${BLUE}Pipex command:${RESET} ./pipex $INFILE \"$CMD1\" \"$CMD2\" $OUTFILE_PIPEX"
        
        # Run Bash pipeline
        eval "< $INFILE $CMD1 | $CMD2 > $OUTFILE_BASH" 2>/dev/null
        BASH_EXIT=$?

        # Run Pipex with or without Valgrind
        if $VALGRIND_MODE; then
            valgrind --leak-check=full --trace-children=yes ./pipex "$INFILE" "$CMD1" "$CMD2" "$OUTFILE_PIPEX" 2>>"$VALGRIND_LOG"
        else
            ./pipex "$INFILE" "$CMD1" "$CMD2" "$OUTFILE_PIPEX" 2>/dev/null
        fi
        PIPEX_EXIT=$?

        # Compare outputs
        if diff "$OUTFILE_BASH" "$OUTFILE_PIPEX" > /dev/null && [ $BASH_EXIT = $PIPEX_EXIT ]; then
            echo -e "${GREEN}✓ Test passed${RESET}"
        else
            echo -e "${RED}✗ Test failed${RESET}"
            echo "Expected output (bash):"
            cat "$OUTFILE_BASH"
            echo " "
            echo "Actual output (pipex):"
            cat "$OUTFILE_PIPEX"
            echo "Bash exit code: $BASH_EXIT"
            echo "Pipex exit code: $PIPEX_EXIT"
        fi
        echo "----------------------"
    done
}

# Main Logic
echo "Starting pipex tests..."
echo "======================"

if $VALGRIND_MODE; then
    echo "Running tests with Valgrind enabled. Logs will be saved to $VALGRIND_LOG."
    > "$VALGRIND_LOG" # Clear previous logs
fi

case "$TEST_TYPE" in
    "all")
        TYPES=("cat" "multi") # Add other test types as required
        for type in "${TYPES[@]}"; do
            run_test_type "$type"
        done
        ;;
    "help"|"-h"|"--help")
        display_usage
        exit 0
        ;;
    *)
        run_test_type "$TEST_TYPE"
        ;;
esac

# Special test: Non-existent input file
if [ "$TEST_TYPE" = "all" ] || [ "$TEST_TYPE" = "error" ]; then
    echo "Testing with non-existent input file..."
    NON_EXISTENT="non_existent_file"
    
    echo -e "${BLUE}Bash command:${RESET} < $NON_EXISTENT cat | wc -l > $OUTFILE_BASH"
    echo -e "${BLUE}Pipex command:${RESET} ./pipex $NON_EXISTENT \"cat\" \"wc -l\" $OUTFILE_PIPEX"
    
    eval "< $NON_EXISTENT cat | wc -l > $OUTFILE_BASH" 2>/dev/null
    BASH_EXIT=$?
    
    if $VALGRIND_MODE; then
        valgrind --leak-check=full --trace-children=yes ./pipex "$NON_EXISTENT" "cat" "wc -l" "$OUTFILE_PIPEX" 2>>"$VALGRIND_LOG"
    else
        ./pipex "$NON_EXISTENT" "cat" "wc -l" "$OUTFILE_PIPEX" 2>/dev/null
    fi
    PIPEX_EXIT=$?
    
    if [ $BASH_EXIT = $PIPEX_EXIT ]; then
        echo -e "${GREEN}✓ Error handling test passed${RESET}"
    else
        echo -e "${RED}✗ Error handling test failed${RESET}"
        echo "Expected exit code: $BASH_EXIT"
        echo "Actual exit code: $PIPEX_EXIT"
    fi
fi

echo "======================"
echo "All tests completed."
