#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "Main.h"
#include "Files.h"

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
	C_LOAD, // "load" is loading all memory from second given from start file
	C_COM // ";" is comment
};

uint8_t switchCommand(char *command){
	if (strcmp(command, "+") == 0) return C_ADD;
	if (strcmp(command, "-") == 0) return C_SUB;
	if (strcmp(command, "=") == 0) return C_EQU;
	if (strcmp(command, "out") == 0) return C_OUT;
	if (strcmp(command, "in") == 0) return C_IN;
	if (strcmp(command, "if") == 0) return C_IF;
	if (strcmp(command, "*") == 0) return C_PLACE;
	if (strcmp(command, "jump") == 0) return C_JUMP;
	if (strcmp(command, "delay") == 0) return C_DELAY;
	if (strcmp(command, "save") == 0) return C_SAVE;
	if (strcmp(command, "quit") == 0) return C_QUIT;
	if (strcmp(command, "draw") == 0) return C_DRAW;
	if (strcmp(command, "load") == 0) return C_LOAD;
	if (strcmp(command, ";") == 0) return C_COM;
	return -1;
}

uint8_t switchDataType(char *type){
	if (strcmp(type, "b") == 0) return 0;
	if (strcmp(type, "c") == 0) return 1;
	if (strcmp(type, "cc") == 0) return 2;
	return -1;
}

void StartCompiling(){
	char *command;
	uint8_t type = -1;
	fprintf(nasm_ptr, "section .data\n\tmem times 256 db 0\nsection .text\n");
	while ((command = readWord(src_ptr)) != NULL){
		type = switchCommand(command);

		switch (type){
			case C_ADD: {
				uint8_t dataType = switchDataType(readWord(src_ptr));
				switch (dataType){
					case 0: {
						fprintf(stderr, "ERR: cannot inc to constant byte\n");
						exit(1);
					}
					case 1: {
						fprintf(
							nasm_ptr,
							"inc byte [mem + %d]\n",
							(uint8_t)(atoi(readWord(src_ptr)))
						);
						break;
					}
					case 2: {
						fprintf(
							nasm_ptr,
							"mov al, [mem + %d]\ninc byte [mem + al]\n",
							(uint8_t)(atoi(readWord(src_ptr)))
						);
						break;
					}
					default: {
						fprintf(stderr, "ERR: unknown data type\n");
						exit(1);
					}
				}
				break;
			}
			case C_SUB: {
				uint8_t dataType = switchDataType(readWord(src_ptr));
				switch (dataType){
					case 0: {
						fprintf(stderr, "ERR: cannot sub constant byte\n");
						exit(1);
					}
					case 1: {
						fprintf(
							nasm_ptr,
							"dec byte [mem + %d]\n",
							(uint8_t)(atoi(readWord(src_ptr)))
						);
						break;
					}
					case 2: {
						fprintf(
							nasm_ptr,
							"mov al, [mem + %d]\ndec byte [mem + al]\n",
							(uint8_t)(atoi(readWord(src_ptr)))
						);
						break;
					}
					default: {
						fprintf(stderr, "ERR: unknown data type\n");
						exit(1);
					}
				}
				break;
			}
			case C_EQU: {
				uint8_t DT1 = switchDataType(readWord(src_ptr));
				uint8_t offset1 = (uint8_t)(atoi(readWord(src_ptr)));
				uint8_t DT2 = switchDataType(readWord(src_ptr));
				char *value;
				switch (DT2){
					case 0: {
						itoa(value, (uint8_t)(atoi(readWord(src_ptr))), 10);
						break;
					}
					case 1: {
						fprintf(
							nasm_ptr, 
							"mov bl, [mem + %d]", 
							(uint8_t)(atoi(readWord(src_ptr)))
						);
						value = "bl";
						break;
					}
					case 2: {
						break;
					}
				}
				switch (DT1){
					case 0: {
						fprintf(stderr, "ERR: cannot move to constant byte\n");
						exit(1);
					}
					case 1: {
						fprintf(
							nasm_ptr, 
							"mov byte [mem + %d], %s\n",
							offset1,
							value
						);
						break;
					}
				}
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
			case C_COM: {
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
