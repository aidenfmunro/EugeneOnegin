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
    FORWARDS  = 1,
    BACKWARDS = 0
};

enum CORRECTFILE
{
    INCORRECT = 0,
    CORRECT   = 1
};

#define swap(a, b, size)						                                           \ 
    do									                                                       \
      {                                                                        \
        size_t _size = size;									                                 \
        char *_a = (char*)&a, *_b = (char*)&b;					                       \
        do								                                                     \
	        {								                                                     \
	          char _temp = *_a;						                                       \
	          *_a++ = *_b;						                                           \
	          *_b++ = _temp;						                                         \
	        } while (--_size > 0);						                                   \ 
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
size_t CheckFile (const char* filename);
size_t getLength(const char* filename);
size_t countLines(const Text* text);
char* parseBuf(Text* text, const char* filename);
char* const* getLinePointers(Text *text);
char* getLine(Text* text, size_t shift);
void bubbleSort(Text* text, compareFunc_t compareFunc);
int compareStringForw(const void* a, const void* b);
int compareStringBack(const void* a, const void* b);




#endif
