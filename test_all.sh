#!/bin/bash

# Script to test CPP modules with comprehensive tests
# Usage: ./test_all.sh [module] [exercise]
# Example: ./test_all.sh cpp_05 ex00

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

test_exercise() {
    local module=$1
    local exercise=$2
    local dir="${module}/${exercise}"
    
    if [ ! -d "$dir" ]; then
        echo -e "${RED}Directory $dir not found${NC}"
        return 1
    fi
    
    echo -e "${YELLOW}=== Testing $module/$exercise ===${NC}"
    cd "$dir"
    
    # Compile with main_test.cpp if it exists
    if [ -f "main_test.cpp" ]; then
        echo -e "${GREEN}Compiling with main_test.cpp...${NC}"
        
        # Backup original main.cpp
        if [ -f "main.cpp" ]; then
            mv main.cpp main.cpp.bak
        fi
        
        # Use main_test.cpp
        cp main_test.cpp main.cpp
        
        # Compile
        make re > /dev/null 2>&1
        
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Compilation successful${NC}"
            
            # Find executable
            EXEC=$(ls -t | grep -v '\.' | head -1)
            
            if [ -n "$EXEC" ] && [ -x "$EXEC" ]; then
                echo -e "${GREEN}Running tests...${NC}"
                ./"$EXEC"
                
                # Check for memory leaks on macOS
                if command -v leaks &> /dev/null; then
                    echo -e "${YELLOW}Checking memory leaks...${NC}"
                    leaks -atExit -- ./"$EXEC" > /dev/null 2>&1
                    if [ $? -eq 0 ]; then
                        echo -e "${GREEN}No memory leaks detected${NC}"
                    else
                        echo -e "${RED}Memory leaks detected!${NC}"
                    fi
                fi
            fi
        else
            echo -e "${RED}Compilation failed${NC}"
        fi
        
        # Restore original main.cpp
        if [ -f "main.cpp.bak" ]; then
            mv main.cpp.bak main.cpp
        fi
        
        make fclean > /dev/null 2>&1
    else
        echo -e "${YELLOW}No main_test.cpp found, using original main.cpp${NC}"
        make re > /dev/null 2>&1
        
        if [ $? -eq 0 ]; then
            EXEC=$(ls -t | grep -v '\.' | head -1)
            if [ -n "$EXEC" ] && [ -x "$EXEC" ]; then
                ./"$EXEC"
            fi
        fi
        
        make fclean > /dev/null 2>&1
    fi
    
    cd - > /dev/null
    echo ""
}

# Main script
if [ $# -eq 2 ]; then
    # Test specific exercise
    test_exercise "$1" "$2"
elif [ $# -eq 1 ]; then
    # Test all exercises in a module
    MODULE=$1
    for ex in ${MODULE}/ex*; do
        if [ -d "$ex" ]; then
            EX=$(basename "$ex")
            test_exercise "$MODULE" "$EX"
        fi
    done
else
    # Test all modules from cpp_05 to cpp_08
    for module in cpp_05 cpp_06 cpp_07 cpp_08; do
        if [ -d "$module" ]; then
            echo -e "${YELLOW}======================================${NC}"
            echo -e "${YELLOW}Testing $module${NC}"
            echo -e "${YELLOW}======================================${NC}"
            for ex in ${module}/ex*; do
                if [ -d "$ex" ]; then
                    EX=$(basename "$ex")
                    test_exercise "$module" "$EX"
                fi
            done
        fi
    done
fi
