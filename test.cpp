#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys\stat.h>


int main ()
{

    struct stat stats = {};

    stat("test1.txt", &stats);

    FILE* fp = fopen("test1.txt", "rb");

    size_t length = stats.st_size / sizeof(char);

    char* buffer = (char*) calloc (length + 1, sizeof(char));
    

    fread(buffer, sizeof(char), length, fp);

    printf("%s\n", buffer);

    printf("%lld\n", length);

    size_t lines = 0;

    size_t i = 0;

    for (i = 0; i < length; i++)
        if (buffer[i] == '\n')
            lines++;
    lines++;

    printf("%lld\n", lines);

    buffer[i + 1] = '\0';

    char** lineptrs = (char**) calloc (lines, sizeof(char*));
    
    lineptrs = &buffer;

    char* textptr = strchr(buffer, '\n');
    while (textptr != NULL)
      {
        *lineptrs = textptr + 1;
        lineptrs++;
        *(textptr - 1) = '\0';
        *textptr = '\0';
        textptr = strchr(buffer, '\n');

        printf("text pointer: %p\n", textptr);
      }

    
    


  

    fclose(fp);

}