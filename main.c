#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define RED "\033[31m"
#define RESET "\033[0m"

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Not enough arguments found. End of programm\n");
        return 0;
    }
    
    FILE* file = fopen(argv[1], "r+");
    if (!file){
        perror(RED"ERROR"RESET);
        return -1;
    }
    
    int regR, regL, textR, textL;
    int c = 0;
    for (int j = 0; j < strlen(argv[2]); j++){
        if (argv[2][j] == '/'){
            switch (c){
                case 0:
                    regL = j + 1;
                    c++;
                    break;
                case 1:
                    regR = j;
                    textL = j + 1;
                    c++;
                    break;
                case 2:
                    textR = j;
                    c++;
                    break;
            }
        }
    }
    if (c!=3){
        printf(RED"ERROR"RESET": mistake in command syntax\n");
        return 1;
    }
    
    char expr[regR-regL+1];
    char text[textR-textL+1];
    expr[regR-regL] = '\0';
    text[textR-textL] = '\0';
    int i = 0;
    for (int j = regL; j < regR; j++){
        printf("expr%d = %c; ", i, argv[2][j]);
        expr[i] = argv[2][j];
        i++;
    }
    printf("\n");
    i = 0;
    for (int j = textL; j < textR; j++){
        printf("text%d = %c; ", i, argv[2][j]);
        text[i] = argv[2][j];
        i++;
    }
    printf("\n");
    
    switch(argv[2][0]){
        case 's':
            printf("%s // %s\n", expr, text);
            int err = ftransform(file, expr, regR-regL, text, textR-textL);
            if (err){
                return -1;
            }
            break;
        /*case '/':
            switch (argv[2][strlen(argv[2])-1]){
                case 'd':
                    int err = fdelete(file, expr, regR-regL);
                    if (err){
                        return -1;
                    }
                    break;
                default:
                    printf("Unknown operation");
                    fclose(file);
                    return 0;
            }
            break;*/
        default:
            printf("Unknown operation");
            fclose(file);
            return 0;
    }
    fclose(file);
    return 0;
}
