#include <stdio.h>
#include <string.h>
#include "utils.h"

int CheckFile (const char* filename)
{
    myAssert (filename, NULLPTR);

    FILE *fp = fopen (filename, "r");
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