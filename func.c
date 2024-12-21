#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define RED "\033[31m"
#define RESET "\033[0m"
#define PURPLE "\033[35m"

int ftransform(FILE* file, char* expr, int exprLen, char* text, int textLen){
    regex_t regex;
    regmatch_t pmatch[1];
    char buf[256];
    int err = regcomp(&regex, expr, REG_EXTENDED);
    if (err){
        regerror(err, &regex, buf, 256);
        printf(RED"ERROR"RESET": %s\n", buf);
        return 1;
    }
    char* strOld;
    ssize_t read;
    size_t len;
    printf("%s // %s\n", expr, text);
    while ((read = getline(&strOld, &len, file)) != -1){
        int c = 0;
        size_t newLen = len - exprLen + textLen + 1;
        char* strNew = malloc(sizeof(char) * newLen);
        if (!strNew){
            perror(RED"ERROR"RESET);
            return -1;
        }
        strNew[newLen - 1] = '\n';
        while ((err = regexec(&regex, strOld, 1, pmatch, 0)) == 0){
            for (int i = 0; i < pmatch[0].rm_so; i++){
                strNew[i] = strOld[i];
            }
            for (int i = pmatch[0].rm_so; i < (pmatch[0].rm_so + textLen); i++){
                strNew[i] = text[i-pmatch[0].rm_so];
            }
            for (int i = pmatch[0].rm_so + textLen; i < newLen; i++){
                strNew[i] = strOld[i - (pmatch[0].rm_so + textLen)];
            }
            printf("%d\n", c);
            c++;
            strcpy(strOld, strNew);
            fseek(file, -len+1, SEEK_CUR);
            fputs(strNew, file);
            fseek(file, 1, SEEK_CUR);
        }
        if (err){
            regerror(err, &regex, buf, 256);
            printf(PURPLE"VERBOSE"RESET": %s\n", buf);
            return -1;
        } 
        free(strNew);
    }
    regfree(&regex);
    return 0;
}
