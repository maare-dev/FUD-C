#include <stdio.h>
#include "Main.h"


enum commands{
    C_ADD, // "+" is adding to first variable value of next
    C_SUB, // "-" is subtracting second value from first variable
    C_EQU, // "=" is writing to first given cell the value of next
    C_OUT, // "out" is printing char given as const or value of cell
    C_IN, // "in" is checking state of key and if pressed jumping
    C_IF, // "if" is checking condition and jumping if true
    C_PLACE, // "*" is just place in code, we can jump there
    C_JUMP, // "jump" is jumping to place with same value ("name")
    C_DELAY, // "delay" is just simple delay for some mills
    C_SAVE, // "save" is saving all to second file given from start
    C_QUIT, // "quit" is exiting with code
    C_DRAW, // "draw" is drawing frame
    C_LOAD // "load" is loading all memory from second given from start file
};


void StartCompiling(){
    char *command;
    while (command = readWord(src_ptr) != NULL){

    }
}