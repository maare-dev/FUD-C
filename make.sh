#!/bin/bash

src=(\
"Main.c" "Main.h" \
"Compiler.c" "Compiler.h" \
"Files.c" "Files.h" \
)

clear
#gcc -Wall -Wextra -o FUD-C ${src[@]}
gcc -o FUD-C ${src[@]}
./FUD-C proj