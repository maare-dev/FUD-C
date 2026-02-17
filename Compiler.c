#include <stdio.h>
#include <string.h>
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

int switchType(char *command){
    if (strcmp(command, "+") == 0) return C_ADD;
    else if (strcmp(command, "-") == 0) return C_SUB;
    else if (strcmp(command, "=") == 0) return C_EQU;
    else if (strcmp(command, "out") == 0) return C_OUT;
    else if (strcmp(command, "in") == 0) return C_IN;
    else if (strcmp(command, "if") == 0) return C_IF;
    else if (strcmp(command, "*") == 0) return C_PLACE;
    else if (strcmp(command, "jump") == 0) return C_JUMP;
    else if (strcmp(command, "delay") == 0) return C_DELAY;
    else if (strcmp(command, "save") == 0) return C_SAVE;
    else if (strcmp(command, "quit") == 0) return C_QUIT;
    else if (strcmp(command, "draw") == 0) return C_DRAW;
    else if (strcmp(command, "load") == 0) return C_LOAD;
    return -1;
}

void StartCompiling(){
    char *command;
    int type = -1;
    while ((command = readWord(src_ptr)) != NULL){
        type = switchType(command);

        switch (type){
            case C_ADD: {
                break;
            }
            case C_SUB: {
                break;
            }
            case C_EQU: {
                break;
            }
            case C_OUT: {
                break;
            }
            case C_IN: {
                break;
            }
            case C_IF: {
                break;
            }
            case C_PLACE: {
                break;
            }
            case C_JUMP: {
                break;
            }
            case C_DELAY: {
                break;
            }
            case C_SAVE: {
                break;
            }
            case C_QUIT: {
                break;
            }
            case C_DRAW: {
                break;
            }
            case C_LOAD: {
                break;
            }
            default: {
                fprintf(stderr, "ERR: unknown command %s\n", command);
                exit(1);
            }
        }
        free(command);
    }
}