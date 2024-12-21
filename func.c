#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define RED "\033[31m"
#define RESET "\033[0m"
#define PURPLE "\033[35m"

int freplacement(FILE* file, char* expr, char* text){
    int exprLen = strlen(expr);
    int textLen = strlen(text);
    int pos = 0;
    if (!expr || !text || !file){
        return -1;
    }

    while(!feof(file)){
        fseek(file, pos, SEEK_SET);
        int matchCount = 0;
        for (int i = 0; i < exprLen; i++){
            if (expr[i] == fgetc(file)){
                matchCount++;
            }
            fseek(file, 1, SEEK_CUR);
        }
        if (matchCount == exprLen){
            fseek(file, pos, SEEK_SET);
            fputs(text, file);
            if (textLen < exprLen){
                
            }
        }
        pos++;
    }
    return 1;
}

int fdeletion(FILE* read, FILE* write, char* expr){
    int exprLen = strlen(expr);
    int posw, posr = 0;
    if (!expr || !read || !write){
        return -1;
    }
    
    while(!feof(read)){
        fseek(write, posw, SEEK_SET);
        fseek(read, posr, SEEK_SET);
        int matchCount = 0;
        for (int i = 0; i < exprLen; i++){
            if (expr[i] == fgetc(read)){
                matchCount++;
            }
            fseek(read, 1, SEEK_CUR);
        }
        if (matchCount == exprLen){
            posr = ftell(read);
        }
        char c = fgetc(read);
        fputc(c, write);
        posw++;
        posr++;
    }
    return 1;
}

int fprefix(FILE* file, char* text){
    if (!file || !text){
        return -1;
    }
    int textLen = strlen(text);
    size_t len;
    ssize_t read;
    char* line;
    while ((read = getline(&line, &len, file)) != -1) {
        char* temp = realloc(line, len + textLen);
        if (!temp){
            perror(RED"ERROR"RESET);
            return -1;
        }
        line = temp;
        memmove(line+textLen, line, len);
        memcpy(line, text, textLen);
        fputs(line, file);
    }
    return 0;
}

int fsuffix(FILE* file, char* text){
    if (!file || !text){
        return -1;
    }
    int textLen = strlen(text);
    size_t len;
    ssize_t read;
    char* line;
    while ((read = getline(&line, &len, file)) != -1) {
        char* temp = realloc(line, len + textLen);
        if (!temp){
            perror(RED"ERROR"RESET);
            return -1;
        }
        line = temp;
        memcpy(line + len, text, textLen);
        fputs(line, file);
    }
    return 0;
}
