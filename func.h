#ifndef FUNC_H
#define FUNC_H

int freplacement(FILE* file, char* expr char* text);
int fdeletion(FILE* read, FILE* write, char* expr);
int fprefix(FILE* file, char* text);
int fsuffix(FILE* file, char* text);

#endif
