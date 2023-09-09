#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include "utils.h"

void CreateText(Text* text, const char* filename)
{
    text->length = getLength(filename);
    text->buffer = parseBuf(text, filename);
    text->lines = getLines(text);
    
    printf("%s\n", text->buffer);
    printf("%lld\n", text->length);
    printf("%lld\n", text->lines);
}

char* parseBuf(Text* text, const char* filename)
{
    FILE* fp = fopen(filename, "rb");

    char* buffer = (char*) calloc (text->length + 1, sizeof(char));
    fread(buffer, sizeof(char), text->length, fp);
    buffer[text->length] = '\0';
  
    fclose(fp);

    return buffer;
}

size_t getLines(Text* text)
{
    size_t lines = 1;
    for (size_t i = 0; i < text->length; i++)
        if (text->buffer[i] == '\n')
            lines++;

    return lines;
}

size_t getLength(const char* filename)
{
    struct stat stats = {};
    stat(filename, &stats);

    return stats.st_size / sizeof(char);
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