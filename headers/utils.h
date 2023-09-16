#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

typedef int(*compareFunc_t) (const void*, const void* );

enum ERRORS
{
    NULLPTR = 0,
    OVERLAP = 1
};

enum SORT
{
    BACKWARDS = 0,
    FORWARDS  = 1,
    NONE      = 2
};

enum CORRECTFILE
{
    INCORRECT = 0,
    CORRECT   = 1
};

#define swap(a, b, size)						                                           \ 
    do									                                                       \
      {                                                                        \
        char *_a = (char*)a, *_b = (char*)b;					                         \
        for (size_t i = 0; i < size; i++)								                       \
	        {								                                                     \
	          char _temp = _a[i];						                                     \
	          _a[i]= _b[i];						                                           \
	          _b[i] = _temp;						                                         \
	        } 						                                                       \ 
      } while (0)


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
    char* const* lineptrs;
    size_t length,
           lines;
};


void CreateText(Text* text, const char* filename, size_t sortmode);

void AppendText(Text* text, const char* filename);

void DestroyText(Text* text);

size_t CheckFile (const char* filename);

size_t getLength(const char* filename);

size_t countLines(const Text* text);

char* parseBuf(Text* text, const char* filename);

char* const* getLinePointers(Text *text);

char* getLine(Text* text, size_t shift);

void freeSpace(void* a);

void generalSort(Text* text, size_t sortmode);

void quickSort(void* array, int start, int end, size_t elemSize, compareFunc_t compareFunc);

int partition(void* array, int left, int right, size_t elemSize, compareFunc_t compareFunc);

void bubbleSort(void* array, size_t lines, const size_t elemSize, compareFunc_t compareFunc);

int compareStringForw(const void* a, const void* b);

int compareStringBack(const void* a, const void* b);

#endif
