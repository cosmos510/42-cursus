#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}Testing CPP_07${NC}"
echo -e "${YELLOW}========================================${NC}"

for ex in ex00 ex01 ex02; do
    if [ -d "$ex" ]; then
        echo -e "\n${GREEN}=== Testing $ex ===${NC}"
        cd "$ex"
        
        
        make re > /dev/null 2>&1
        
        if [ $? -eq 0 ]; then
            EXEC=$(find . -maxdepth 1 -type f -perm +111 ! -name "*.sh" | head -1)
            if [ -n "$EXEC" ]; then
                $EXEC
                
                if command -v leaks &> /dev/null; then
                    echo -e "${YELLOW}Checking leaks...${NC}"
                    leaks -atExit -- $EXEC > /dev/null 2>&1 && echo -e "${GREEN}No leaks${NC}" || echo -e "${RED}Leaks detected${NC}"
                fi
            fi
        else
            echo -e "${RED}Compilation failed${NC}"
        fi
        
        make fclean > /dev/null 2>&1
        cd ..
    fi
done
