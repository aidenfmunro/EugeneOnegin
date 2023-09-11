#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <ctype.h>
#include "utils.h"

void CreateText(Text* text, const char* filename)
{
    myAssert(text, NULLPTR);

    text->length = getLength(filename);
    text->buffer = parseBuf(text, filename);
    text->lines = countLines(text);
    text->lineptrs = getLinePointers(text);

    printf("%s\n", text->buffer);
    putchar('\n');
    printf("%lld\n", text->length);
    putchar('\n');
    printf("%lld\n", text->lines);
    putchar('\n');

    /*
    for (size_t i = 0; i < text->lines; i++)
      {
        printf("%lld: %p\n", i + 1, getLine(text, i));
      }
    */

    putchar('\n');

    bubbleSort(text, &compareString);

    putchar('\n');

    for (size_t i = 0; i < text->lines; i++)
      {
        printf("%lld: %s\n", i + 1, *getLine(text, i));
      }


}

char** getLinePointers(Text *text)
{
    char** lineptrs = (char**)calloc(text->lines, sizeof(char*));
    
    *lineptrs = text->buffer;

    char* textptr = strchr(text->buffer, '\n');

    while (textptr != NULL)
      {
        *textptr = '\0'; // \n -> \0
        lineptrs++;
        *lineptrs = textptr + 1;
        // *(textptr - 1) = '\0'; // \r -> \0
        char* tempptr = textptr;
        textptr = strchr(tempptr + 1, '\n'); 
      }

    lineptrs -= (text->lines - 1);

    return lineptrs;
}

char* parseBuf(Text* text, const char* filename)
{   
    myAssert(text, NULLPTR);

    FILE* fp = fopen(filename, "rb");

    char* buffer = (char*)calloc(text->length + 1, sizeof(char));
    fread(buffer, sizeof(char), text->length, fp);
    buffer[text->length] = '\0';
  
    fclose(fp);

    return buffer;
}

size_t getLength(const char* filename)
{
    struct stat stats = {};
    stat(filename, &stats);

    return stats.st_size / sizeof(char);
}

size_t countLines(Text* text)
{
    myAssert(text, NULLPTR);

    size_t lines = 1;
    for (size_t i = 0; i < text->length; i++)
        if (text->buffer[i] == '\n')
            lines++;

    return lines;
}

char** getLine(Text* text, size_t shift)
{
    myAssert(shift < text->lines, OVERLAP);

    return text->lineptrs + shift;
}

void bubbleSort(Text* text, int(*compareString)(void* a, void* b))
{
    myAssert(text, NULLPTR);

    for (size_t i = 0; i < text->lines - 1; i++)
      for (size_t j = 0; j < text->lines - 1 - i; j++)
        {
          char** str1 = getLine(text, j);
          char** str2 = getLine(text, j + 1);
          
          if (compareString(str1, str2) > 0)
            {
              swap(str1, str2);
            }
        }             
}   

void swap(char** ptr1, char** ptr2) 
{   
    myAssert(ptr1, NULLPTR);
    myAssert(ptr2, NULLPTR);

    char* temp = *ptr2;
    *ptr2 = *ptr1;
    *ptr1 = temp;
}

int compareString(void* a, void* b)
{
    char* strptr1 = *(char**) a;
    char* strptr2 = *(char**) b;

    while(*strptr1 != '\0' && *strptr1 != '\r' && !isalpha(*strptr1))
        strptr1++;
    while(*strptr2 != '\0' && *strptr2 != '\r' && !isalpha(*strptr2))
        strptr2++;

    while(*strptr1 == *strptr2)
      {
        strptr1++;
        strptr2++;
      }
  
    return *strptr1 - *strptr2;
} 


size_t CheckFile (const char* filename)
{
    myAssert (filename, NULLPTR);

    FILE* fp = fopen (filename, "rb");
        if (fp == NULL)
          {
            printf ("Unable to open file\n");
            return INCORRECT;
          }

    fclose (fp);

    char* dotptr = strchr (filename, (int)('.')) + 1;

    if(strcmp ("txt", dotptr) || strcmp ("doc", dotptr) ||  strcmp ("docx", dotptr) || strcmp ("rtf", dotptr))
      {
        return CORRECT;
      }
    
    return INCORRECT;
}


/*
int compareFunc(void* a, void* b)
{

}
*/

/*
int compareInt(void* a, void* b)
{
    return *(const int*) a - *(const int*) b;
}
*/
