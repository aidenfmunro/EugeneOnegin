#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

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
int CheckFile (const char* filename);
size_t getLength(const char* filename);
size_t countLines(Text* text);
char* parseBuf(Text* text, const char* filename);
char** getLinePointers(Text *text);
void bubbleSort(Text* text);
void swap(char* ptr1, char* ptr2);




#endif
