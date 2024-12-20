#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define RED "\033[31m"
#define RESET "\033[0m"

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
    while ((read = getline(&strOld, &len, file)) != -1){
        size_t newLen = len - exprLen + textLen;
        char* strNew = malloc(sizeof(char) * newLen);
        while ((err = regexec(&regex, expr, 1, pmatch, 0)) == 0){
            for (int i = 0; i < pmatch[0].rm_so; i++){
                strNew[i] = strOld[i];
            }
            for (int i = pmatch[0].rm_so; i < (pmatch[0].rm_so + textLen); i++){
                strNew[i] = text[i-pmatch[0].rm_so];
            }
            for (int i = pmatch[0].rm_so + textLen; i < newLen; i++){
                strNew[i] = strOld[i - (pmatch[0].rm_so + textLen)];
            }
        }
        fseek(file, -len, SEEK_CUR);
        fputs(strNew, file);
        free(strNew);
    }
    regfree(&regex);
    return 0;
}
