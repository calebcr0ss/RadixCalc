#!/bin/bash
set -e
echo ""
echo "Compiled for you."
echo "If doesnt work properly make sure you are inside the project folder"

gcc radixCalc.c -Wall -Wextra -Werror -o radixCalc -lm

