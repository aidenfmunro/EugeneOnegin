#include <stdio.h>
#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
      {
        printf("Please type in text file names.");  
      }
    else if (CheckFile(argv[1]) && CheckFile(argv[2]))
      {

      }
}


