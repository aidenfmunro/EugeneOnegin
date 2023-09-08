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
    buffer[length] = '\0';
    fread(buffer, sizeof(char), length, fp);
    


    fclose(fp);

    printf("%s\n", buffer);

    printf("%lld\n", length);

    size_t lines = 1;

    for (size_t i = 0; i < length; i++)
        if (buffer[i] == '\n')
            lines++;

    printf("%lld\n", lines);


    char** lineptrs = (char**)calloc(lines, sizeof(char*));
    
    lineptrs = &buffer;

    char* textptr = strchr(buffer, '\n');

    while (textptr != NULL)
      {
        *textptr = '\0';
        *lineptrs = textptr + 1;
        lineptrs++;
        *(textptr - 1) = '\0';
        printf("text pointer: %p\n", textptr);
        textptr = strchr(textptr + 1, '\n'); 

      }

    
    


  


}