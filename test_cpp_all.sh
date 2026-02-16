#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║  CPP MODULES 05-08 COMPREHENSIVE TEST ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
echo ""

for module in cpp_05 cpp_06 cpp_07 cpp_08; do
    if [ -d "$module" ] && [ -f "$module/test.sh" ]; then
        echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
        echo -e "${YELLOW}Testing $module${NC}"
        echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
        cd "$module"
        ./test.sh
        cd ..
        echo ""
    fi
done

echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║           ALL TESTS COMPLETED          ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
