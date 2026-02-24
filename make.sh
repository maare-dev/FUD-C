#!/bin/bash

src=(\
"Main.c" "Main.h" \
"Compiler.c" "Compiler.h" \
"Files.c" "Files.h" \
)
if [ -z $1 ]; then
    clear
    #gcc -Wall -Wextra -o FUD-C ${src[@]}
    gcc -o FUD-C ${src[@]}
    ./FUD-C proj
else
    case $1 in
        "test_lib")
        clear
        gcc -o fud11_test fud11_test.c -lX11
        ./fud11_test
        ;;
    *)
    ;;
    esac
fi