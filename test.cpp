#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys\stat.h>

void bubbleSort(char** lineptrs, size_t lines);
void swap(char* ptr1, char* ptr2);

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
    
    *lineptrs = buffer;

    printf("%p\n", buffer);

    char* textptr = strchr(buffer, '\n');

    while (textptr != NULL)
    {
        *textptr = '\0'; // \n -> \0
        lineptrs++;
        *lineptrs = textptr + 1;
        // *(textptr - 1) = '\0'; // \r -> \0
        // printf("text pointer: %p\n", textptr);
        char* tempptr = textptr;
        textptr = strchr(tempptr + 1, '\n'); 
    }

    lineptrs -= (lines);

    // printf("%p\n", *lineptrs);
    
    // printf("%p\n", *(lineptrs + 1));

     bubbleSort(lineptrs, lines);

    for (size_t i = 0; i < lines; i++)
      {
        printf("%p\n", *(lineptrs + i));
      }
    
    printf("%s", *(lineptrs + 1));
    
    for (size_t i = 1; i < lines; i++)
    {
        printf("%s\n", *(lineptrs + i));
    }
}

void bubbleSort(char** lineptrs, size_t lines)
{
  for (size_t i = 0; i < lines - 1; i++)
    for (size_t j = 1; j < lines - 1 - j; j++)
         if (strcmp(*(lineptrs + j), *(lineptrs + j + 1)) < 0)
          {
            swap(*(lineptrs + j), *(lineptrs + j + 1));
          }       
}   

void swap(char* ptr1, char* ptr2)
{
    char* temp = ptr2;
    *ptr2 = *ptr1;
    *ptr1 = *temp;
}
