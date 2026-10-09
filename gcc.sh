#!/bin/bash
set -e
echo ""
echo "Compiled for you."
echo "If doesnt work properly make sure you are inside the project folder"
# weirdo why do you read the compilation script just run it and be quiet dirty boi luv u
gcc radixCalc.c -Wall -Wextra -Werror -o radixCalc -lm


