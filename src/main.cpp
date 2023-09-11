#include <stdio.h>
#include "utils.h"

int main (int argc, char* argv[])
{
    if (argc < 2)
      {
        printf ("Please type in two text file names.");  
      }
    else if (CheckFile (argv[1]) && CheckFile (argv[2]))
      {
        Text original = {};
        // printf("%lld", getLength(argv[1]));
        CreateText(&original, argv[1]);
        AppendText(&original, argv[2]);
      }
}


