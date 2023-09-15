#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <ctype.h>
#include "utils.h"

void CreateText(Text* text, const char* filename, size_t sortmode)
{
    myAssert(text, NULLPTR);

    text->length = getLength(filename);
    text->buffer = parseBuf(text, filename);
    text->lines = countLines(text);
    text->lineptrs = getLinePointers(text);

    putchar('\n');
    printf("size: %lld\n", text->length);
    putchar('\n');
    printf("lines: %lld\n", text->lines);
    putchar('\n');

    generalSort(text, sortmode);
  
    for (size_t i = 0; i < text->lines; i++)
      {
        printf("%lld: %s\n", i + 1, getLine(text, i));
      }
}

void AppendText(Text* text, const char* filename)
{
  myAssert(text, NULLPTR);

  FILE* fp = fopen(filename, "a");

  for (size_t i = 0; i < text->lines; i++)
    {
      char* str = getLine(text, i);
      if (*str != '\r') //skip lines with spaces
          fputs(str, fp);
    }
  fputs("---------------------------------------------\n", fp);

  fclose(fp);

  free((void*)text->lineptrs);  
}

char* const* getLinePointers(Text *text)
{
    char** lineptrs = (char**)calloc(text->lines, sizeof(char*));
    
    *lineptrs = text->buffer;

    char* textptr = strchr(text->buffer, '\n');

    while (textptr != NULL)
      {
        *textptr = '\0'; // \n -> \0
        lineptrs++;
        *lineptrs = textptr + 1;
        textptr = strchr(textptr + 1, '\n'); 
      }

    lineptrs -= (text->lines - 1);

    return  (char* const*)lineptrs;

    free((void*)text->buffer);
}

char* parseBuf(Text* text, const char* filename)
{   
    myAssert(text, NULLPTR);

    FILE* fp = fopen(filename, "rb");

    char* buffer = (char*)calloc(text->length + 2, sizeof(char));
    fread(buffer, sizeof(char), text->length, fp);
    buffer[text->length] = '\r';
    buffer[text->length + 1] = '\0';
  
    fclose(fp);

    return buffer;
}

size_t getLength(const char* filename)
{
    struct stat stats = {};
    stat(filename, &stats);

    return stats.st_size / sizeof(char);
}

size_t countLines(const Text* text)
{
    myAssert(text, NULLPTR);

    size_t lines = 1;
    for (size_t i = 0; i < text->length; i++)
        if (text->buffer[i] == '\n')
            lines++;

    return lines;
}

char* getLine(Text* text, size_t numLine)
{
    myAssert(numLine < text->lines, OVERLAP); // out of bounds

    return *(text->lineptrs + numLine);
}

void generalSort(Text* text, size_t sortmode)
{
    if (sortmode == FORWARDS)
        bubbleSort((void*)text->lineptrs, text->lines, sizeof(text->lineptrs[0]), compareStringForw);
    else if (sortmode == BACKWARDS)
        bubbleSort((void*)text->lineptrs, text->lines, sizeof(text->lineptrs[0]), compareStringBack);
}

void bubbleSort(void* array, size_t numElems, const size_t elemSize, compareFunc_t compareFunc)
{
    myAssert(array, NULLPTR);
    myAssert(numElems, NULLPTR);
    myAssert(elemSize, NULLPTR);

    for (size_t i = 0; i < numElems - 1; i++)
      for (size_t j = 0; j < numElems - 1 - i; j++)
        {
          // (?) по логике здесь не должно быть функции getLine т.к. compareFunc должен принимать
          // принимаемые функицей bubbleSort значения.

          if (compareFunc(array + j * elemSize, array + (j + 1) * elemSize) > 0)
            {
              swap(array + j * elemSize,  array + (j + 1) * elemSize, elemSize);
            }
        }             
}


int compareStringForw(const void* a, const void* b)
{
    myAssert(a, NULLPTR);
    myAssert(b, NULLPTR);

    char* strptr1 = *(char**) a;
    char* strptr2 = *(char**) b; 
  
    while (*strptr1 != '\0' && *strptr1 != '\r' && !isalpha(*strptr1))
        strptr1++;
    while (*strptr2 != '\0' && *strptr2 != '\r' && !isalpha(*strptr2))
        strptr2++;

    while (*strptr1 == *strptr2 && *strptr1 != '\0' && *strptr2 != '\0')
      {
        strptr1++;
        strptr2++;
      }
       
    return  *strptr1 - *strptr2;
}

int compareStringBack(const void* a, const void* b)
{
    myAssert(a, NULLPTR);
    myAssert(b, NULLPTR);

    char* strptr1 = *(char**) a;
    char* strptr2 = *(char**) b; 

    char* fixptr1 = *(char**) a;
    char* fixptr2 = *(char**) b; 
  
    while (*strptr1 != '\r')
        strptr1++;
    while (*strptr2 != '\r')
        strptr2++;
    
    while (!isalpha(*strptr1) && strptr1 > fixptr1)
        strptr1--;
    while (!isalpha(*strptr2) && strptr2 > fixptr2)
        strptr2--;
  
    while (*strptr1 == *strptr2 && strptr1 > fixptr1  && strptr2 > fixptr2)
      {
        strptr1++;
        strptr2++;
      }
       
    return  *strptr1 - *strptr2;
} 

size_t CheckFile(const char* filename)
{
    myAssert(filename, NULLPTR);

    FILE* fp = fopen(filename, "rb");
        if (fp == NULL)
          {
            printf("Unable to open file\n");
            return INCORRECT;
          }

    fclose(fp);

    char* dotptr = strchr(filename, (int)('.')) + 1;

    if(strcmp("txt", dotptr) || strcmp("doc", dotptr) ||  strcmp("docx", dotptr) || strcmp("rtf", dotptr))
      {
        return CORRECT;
      }
    
    return INCORRECT;
}

void freeSpace(void* a)
{
    free(a);
}

/*
void deleteSpaces(Text* text, const char* filename)
{
  myAssert(text, NULLPTR);
  myAssert(filename, NULLPTR);

  FILE* fp = fopen(filename, "rb");

  
}
*/