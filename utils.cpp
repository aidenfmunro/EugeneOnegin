#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
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

    for (size_t i = 0; i < text->lines; i++)
      {
        printf("%p\n", *(text->lineptrs + i));
      }

    putchar('\n');

    bubbleSort(text);

    putchar('\n');

    for (size_t i = 0; i < text->lines; i++)
      {
        printf("%s\n", *(text->lineptrs + i));
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

    char* buffer = (char*) calloc (text->length + 1, sizeof(char));
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

char* getLine(Text* text, size_t shift)
{
    myAssert(0 <= shift < text->lines, OVERLAP);

    return *(text->lineptrs + shift);
}

void bubbleSort(Text* text)
{
    myAssert(text, NULLPTR);

    for (size_t i = 0; i < text->lines - 1; i++)
      for (size_t j = 1; j < text->lines - 1 - j; j++)
          if (strcmp(getLine(text, j), getLine(text, j + 1)) > 0)
            {
              swap(getLine(text, j), getLine(text, j + 1));
            }       
}   

void swap(char* ptr1, char* ptr2)
{   
    myAssert(ptr1, NULLPTR);
    myAssert(ptr2, NULLPTR);

    char* temp = ptr2;
    *ptr2 = *ptr1;
    *ptr1 = *temp;
}

int CheckFile (const char* filename)
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