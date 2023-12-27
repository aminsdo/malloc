#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

while read -r line;do
    echo "$line"
    LD_PRELOAD=./libmalloc.so $line > out1
    if [ $? -eq 0 ];then
        echo -e "${GREEN}success${NC}"
    else
        echo -e "${RED}failed${NC}"
    fi
    echo
done < tests/input
rm out1
exit 0
