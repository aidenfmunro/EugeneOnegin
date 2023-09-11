#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

typedef int (compareString_t)(void* a, void* b);

enum ERRORS
{
    NULLPTR = 0,
    OVERLAP = 1
};

enum CORRECTFILE
{
    INCORRECT = 0,
    CORRECT   = 1
};

#define myAssert(EXPRESSION, ERROR_CODE)                                       \
    if (!(EXPRESSION))                                                         \
      {                                                                        \
        fprintf (stderr,"%s, failed at %s:%d\n", #ERROR_CODE                   \
        , __FILE__, __LINE__);                                                 \
        exit(ERROR_CODE);                                                      \
      }

struct Text 
{
    char*  buffer;
    char** lineptrs;
    size_t length,
           lines;
};


void CreateText(Text* text, const char* filename);
size_t CheckFile (const char* filename);
size_t getLength(const char* filename);
size_t countLines(Text* text);
char* parseBuf(Text* text, const char* filename);
char** getLinePointers(Text *text);
char** getLine(Text* text, size_t shift);
void bubbleSort(Text* text, int(*compareString)(void* a, void* b));
void swap(char** ptr1, char** ptr2);
int compareString(void* a, void* b);



#endif
