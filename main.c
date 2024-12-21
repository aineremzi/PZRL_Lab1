#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define RED "\033[31m"
#define RESET "\033[0m"

int main(int argc, char* argv[]){
    if (argc < 4){
        printf("Not enough arguments found. End of programm\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r+");
    if (!file){
        perror(RED"ERROR"RESET);
        return -1;
    }

    if (argv[2][0] != '-'){
        printf("Expected flag after file destination\n");
        return 1;
    }
    switch(argv[2][1]){
        case 'r':
            if (argc < 5){
                printf("Expected two arguments after '-r' flag\n");
                return 1;
            }
            int err = freplacement(file, argv[3], argv[4]);
            if (err){
                return err;
            }
            break;
        case 'd':
            FILE* write = fopen(argv[1], "w");
            if (!write){
                perror(RED"ERROR"RESET);
                return -1;
            }
            err = fdeletion(file, write, argv[3]);
            if (err){
                return err;
            }
            break;
        case 'i':
            if (argc < 5){
                printf("Expected flag and two more arguments\n");
                return 1;
            }
            if (argv[3][0]!='-'){
                printf("Expected flag after '-i'\n");
                return 1;
            }
            switch (argv[3][1]){
                case 'f':
                    err = fprefix(file, argv[4]);
                    if (err){
                        return err;
                    }
                    break;
                case 'b':
                    err = fsuffix(file, argv[4]);
                    if (err){
                        return err;
                    }
                    break;
                default:
                    printf("Unknown flag after '-i'\n");
                    return 1;
            }
            default:
            printf("Unknown flag\n");
            return 1;
    }
    return 0;
}
