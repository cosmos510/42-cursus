#!/bin/bash

# Clean up previous test output if any
rm -f test.txt.replace

# Run your program
./ex04 test.txt Hello Hi

# Check the result
echo "=== Output file content ==="
cat test.txt.replace