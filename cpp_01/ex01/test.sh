#!/bin/bash

# Check if user provided an argument
if [ $# -ne 1 ]; then
    echo "Usage: ./test.sh <horde_size>"
    exit 1
fi

HORDE_SIZE=$1

# Step 1: Build
echo "Compiling project..."
make re
if [ $? -ne 0 ]; then
    echo "Compilation failed ❌"
    exit 1
fi
echo "Compilation succeeded ✅"

# Step 2: Run the executable with the horde size
echo -e "\nRunning executable with horde size = $HORDE_SIZE...\n"
./ex01 "$HORDE_SIZE"

# Step 3: Leak check (optional for macOS users)
if command -v leaks &> /dev/null; then
    echo -e "\nChecking for memory leaks...\n"
    leaks --atExit -- ./ex01 "$HORDE_SIZE"
fi