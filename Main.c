#include <stdio.h>
#include <string.h>
#include "Files.h"
#include "Compiler.h"

enum modes{
    NORMAL,
    DEBUG
};
int mode = NORMAL;
FILE *src_ptr;
FILE *exe_ptr;
int main(const int argc, const char **argv) {

    if (argc == 1){
        fprintf(stderr, "ERR: no arguments\n");
        return 1;
    }
    else if (argc == 2){
        src_ptr = SaveOpenFile(src_ptr, argv[1], "r");
        char *exe_name = argv[1];
        strcat(exe_name, ".exe");
        exe_ptr = SaveOpenFile(exe_ptr, exe_name, "w");
    }
    else if(argc == 3){
        if (strcmp(argv[1], "-n") == 0){
            mode = NORMAL;
            src_ptr = SaveOpenFile(src_ptr, argv[2], "r");
            char *exe_name = argv[2];
            strcat(exe_name, ".exe");
            exe_ptr = SaveOpenFile(exe_ptr, exe_name, "w");
        }
        else if (strcmp(argv[1], "-d") == 0){
            mode = DEBUG;
            src_ptr = SaveOpenFile(src_ptr, argv[2], "r");
            char *exe_name = argv[2];
            strcat(exe_name, ".exe");
            exe_ptr = SaveOpenFile(exe_ptr, exe_name, "w");
        }
        else{
            src_ptr = SaveOpenFile(src_ptr, argv[1], "r");
            exe_ptr = SaveOpenFile(exe_ptr, argv[2], "w");
        }
    }
    else if (argc == 4){
        //mode
        if (strcmp(argv[1], "-n") == 0){
            mode = NORMAL;
        }
        else if (strcmp(argv[1], "-d") == 0){
            mode = DEBUG;
        }
        //files
        src_ptr = SaveOpenFile(src_ptr, argv[2], "r");
        exe_ptr = SaveOpenFile(exe_ptr, argv[3], "w");
    }
    StartCompiling();

    return 0;
}