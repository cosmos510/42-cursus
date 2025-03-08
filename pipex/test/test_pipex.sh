#!/bin/bash

# Colors for output
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

# Test files
INFILE="./../files/infile"
OUTFILE_BASH="outfile_bash"
OUTFILE_PIPEX="outfile_pipex"

# Function to display usage
display_usage() {
    echo "Usage: $0 [test_type]"
    echo "Available test types:"
    echo "  all        - Run all tests (default)"
    echo "  cat        - Run cat related tests"
    echo "  grep       - Run grep related tests"
    echo "  ls         - Run ls related tests"
    echo "  tr         - Run tr related tests"
    echo "  sed        - Run sed related tests"
    echo "  head       - Run head/tail related tests"
    echo "  awk        - Run awk related tests"
    echo "  sort       - Run sort related tests"
    echo "  cut        - Run cut related tests"
    echo "  rev        - Run rev related tests"
    echo "  error      - Run error cases tests"
    echo "  complex    - Run complex combinations tests"
    echo "  special    - Run special characters tests"
    echo "  multi      - Run multiple command chained tests"
}

# Check if test files exist
if [ ! -f "$INFILE" ]; then
    echo -e "${RED}Error:${RESET} Test file '$INFILE' not found."
    exit 1
fi

# Function to run tests for a specific type
run_test_type() {
    local test_type=$1
    
    case $test_type in
        "cat")
            COMMANDS=(
                "cat|wc -l"
                "cat|wc -w"
                "cat|wc -c"
                "cat|sort"
                "cat|sort -r"
            )
            ;;
        "grep")
            COMMANDS=(
                "grep test|wc -l"
                "grep -i TEST|wc -l"
                "grep 42|wc -w"
                "grep -v test|wc -l"
                "grep -c test|wc -l"
                "grep .|wc -l"
                "grep -n test|wc -l"
                "grep -l test|wc -l"
                "grep -w test|wc -l"
                "grep -e test|wc -l"
            )
            ;;
        "ls")
            COMMANDS=(
                "ls -l|wc -l"
                "ls -la|wc -l"
                "ls -R|wc -l"
                "ls -t|wc -l"
                "ls|sort"
                "ls|sort -r"
                "ls -l|grep ^d"
            )
            ;;
        "tr")
            COMMANDS=(
                "cat|tr a-z A-Z"
                "cat|tr e E"
                "cat|tr -d '\n'"
                "cat|tr -s '\n'"
                "cat|tr -d 'aeiou'"
                "cat|tr '[a-z]' '[A-Z]'"
                "cat|tr '[:lower:]' '[:upper:]'"
            )
            ;;
        "sed")
            COMMANDS=(
                "cat|sed s/test/TEST/g"
                "cat|sed s/$/./"
            )
            ;;
        "head")
            COMMANDS=(
                "head -n 5|tail -n 2"
                "head -c 20|wc -c"
                "tail -n 3|head -n 1"
                "head -n 10|tail -n 5"
            )
            ;;
        "awk")
            COMMANDS=(
                "awk {print \$1}|wc -l"
                "awk {print NF}|wc -l"
                "awk {print length}|sort -n"
                "awk /test/|wc -l"
            )
            ;;
        "sort")
            COMMANDS=(
                "sort|uniq"
                "sort -r|head"
                "sort -n|tail"
                "sort|uniq -c"
                "sort -u|wc -l"
            )
            ;;
        "cut")
            COMMANDS=(
                "cut -c1-5|wc -l"
                "cut -d: -f1|uniq"
                "cut -d' ' -f2|grep a"
            )
            ;;
        "rev")
            COMMANDS=(
                "rev|rev"
                "rev|wc -l"
                "rev|sort"
                "rev|grep test"
                "rev|cut -c1-5"
            )
            ;;
        "error")
            COMMANDS=(
                "invalid_cmd|wc -l"
                "ls|invalid_cmd"
                "|wc -l"
                "cat ''|wc -l"
                "cat no_such_file|wc -l"
                "'ls -l'|wc -l"
                "ls .|wc -l"
            )
            ;;
        "special")
            COMMANDS=(
                "grep '*'|wc -l"
                "grep '\['|wc -l"
            )
            ;;
        "multi")
            COMMANDS=(
                "cat|grep test|wc -l"
                "cat|sort|uniq|wc -l"
                "grep test|cut -c1-5|sort|uniq"
                "cat|tr 'a-z' 'A-Z'|grep TEST|wc -l"
                "cat|awk {print \$1}|sort|uniq -c"
                "cat|head -n 5|tail -n 2|wc -l"
                "ls -la|grep ^d|wc -l"
                "cat|sed s/test/TEST/g|grep TEST|wc -l"
                "cat|rev|cut -c1-3|sort|uniq"
            )
            ;;
        *)
            echo "Unknown test type: $test_type"
            return 1
            ;;
    esac

    echo "Running $test_type tests..."
    for test_case in "${COMMANDS[@]}"; do
        # Split the test case into two commands
        CMD1=$(echo "$test_case" | cut -d'|' -f1)
        CMD2=$(echo "$test_case" | cut -d'|' -f2)
        
        # Display commands
        echo -e "${BLUE}Bash command:${RESET} < $INFILE $CMD1 | $CMD2 > $OUTFILE_BASH"
        echo -e "${BLUE}Pipex command:${RESET} ./../pipex $INFILE \"$CMD1\" \"$CMD2\" $OUTFILE_PIPEX"
        
        # Execute commands
        eval "< $INFILE $CMD1 | $CMD2 > $OUTFILE_BASH" 2>/dev/null
        BASH_EXIT=$?
        
        ./../pipex "$INFILE" "$CMD1" "$CMD2" "$OUTFILE_PIPEX" 2>/dev/null
        PIPEX_EXIT=$?
        
        # Compare results
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

# Function to run multi-command tests
run_multi_command_test() {
    local input_file=$1
    shift
    local commands=("$@")
    local num_commands=${#commands[@]}

    # Bash pipeline
    bash_cmd="< $input_file"
    for ((i=0; i<num_commands; i++)); do
        bash_cmd+=" ${commands[i]}"
        if [ $i -lt $((num_commands-1)) ]; then
            bash_cmd+=" |"
        fi
    done
    bash_cmd+=" > $OUTFILE_BASH"

    # Pipex command
    pipex_cmd="./../pipex $input_file"
    for cmd in "${commands[@]}"; do
        pipex_cmd+=" \"$cmd\""
    done
    pipex_cmd+=" $OUTFILE_PIPEX"

    # Display commands
    echo -e "${BLUE}Bash command:${RESET} $bash_cmd"
    echo -e "${BLUE}Pipex command:${RESET} $pipex_cmd"

    # Execute commands
    eval "$bash_cmd" 2>/dev/null
    BASH_EXIT=$?

    eval "$pipex_cmd" 2>/dev/null
    PIPEX_EXIT=$?

    # Compare results
    if diff "$OUTFILE_BASH" "$OUTFILE_PIPEX" > /dev/null && [ $BASH_EXIT = $PIPEX_EXIT ]; then
        echo -e "${GREEN}✓ Multi-command Test passed${RESET}"
    else
        echo -e "${RED}✗ Multi-command Test failed${RESET}"
        echo "Expected output (bash):"
        cat "$OUTFILE_BASH"
        echo " "
        echo "Actual output (pipex):"
        cat "$OUTFILE_PIPEX"
        echo "Bash exit code: $BASH_EXIT"
        echo "Pipex exit code: $PIPEX_EXIT"
    fi
    echo "----------------------"
}

# Process argument
TEST_TYPE=${1:-"all"}

echo "Starting pipex tests..."
echo "======================"

case "$TEST_TYPE" in
    "all")
        TYPES=("cat" "grep" "ls" "tr" "sed" "head" "awk" "sort" "cut" "rev" "error" "complex" "special" "multi")
        for type in "${TYPES[@]}"; do
            run_test_type "$type"
        done
        ;;
    "help"|"-h"|"--help")
        display_usage
        exit 0
        ;;
    "multi")
        # Example multi-command tests
        run_multi_command_test "$INFILE" "cat" "grep test" "wc -l"
        run_multi_command_test "$INFILE" "cat" "sort" "uniq" "wc -l"
        run_multi_command_test "$INFILE" "cat" "tr 'a-z' 'A-Z'" "grep TEST" "wc -l"
        run_multi_command_test "$INFILE" "cat" "grep -v test" "wc -l"
    run_multi_command_test "$INFILE" "ls -l" "grep ^d" "wc -l"
    run_multi_command_test "$INFILE" "cat" "tr '[:lower:]' '[:upper:]'" "sort" "uniq"
    run_multi_command_test "$INFILE" "cat" "awk {print \$NF}" "sort" "uniq -c"
    run_multi_command_test "$INFILE" "grep '^[aeiou]' " "cut -c1-5" "sort" "uniq"
    run_multi_command_test "$INFILE" "cat" "rev" "cut -c1-5" "sort" "uniq"
    run_multi_command_test "$INFILE" "cat" "sed s/test/TEST/g" "grep TEST" "wc -l"
    run_multi_command_test "$INFILE" "head -n 10" "grep test" "wc -l"
    run_multi_command_test "$INFILE" "cat" "awk NF > 2" "sort" "uniq -c"
    run_multi_command_test "$INFILE" "cat" "tr -d '[:space:]'" "wc -c"
    run_multi_command_test "$INFILE" "ls -la" "awk {print \$NF}" "grep test" "wc -l"

        ;;
    *)
        run_test_type "$TEST_TYPE"
        ;;
esac

# Special case: test with non-existent input file
if [ "$TEST_TYPE" = "all" ] || [ "$TEST_TYPE" = "error" ]; then
    echo "Testing with non-existent input file..."
    NON_EXISTENT="non_existent_file"
    
    echo -e "${BLUE}Bash command:${RESET} < $NON_EXISTENT cat | wc -l > $OUTFILE_BASH"
    echo -e "${BLUE}Pipex command:${RESET} ./../pipex $NON_EXISTENT \"cat\" \"wc -l\" $OUTFILE_PIPEX"
    
    eval "< $NON_EXISTENT cat | wc -l > $OUTFILE_BASH" 2>/dev/null
    BASH_EXIT=$?
    ./pipex "$NON_EXISTENT" "cat" "wc -l" "$OUTFILE_PIPEX" 2>/dev/null
    PIPEX_EXIT=$?
    
    if [ $BASH_EXIT = $PIPEX_EXIT ]; then
        echo -e "${GREEN}✓ Error handling test passed${RESET}"
    else
        echo -e "${RED}✗ Error handling test failed${RESET}"
        echo "Expected exit code: $BASH_EXIT"
        echo "Actual exit code: $PIPEX_EXIT"
    fi
fi

# Cleanup
#rm -f "$OUTFILE_BASH" "$OUTFILE_PIPEX"

echo "======================"
echo "All tests completed."