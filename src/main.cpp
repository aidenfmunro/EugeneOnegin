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
        Text textStartToEnd = {};
        Text textEndToStart = {};

        CreateText(&original, argv[1], NONE);
        AppendText(&original, argv[2]);
  
        CreateText(&textStartToEnd, argv[1], FORWARDS);
        AppendText(&textStartToEnd, argv[2]);

        CreateText(&textEndToStart, argv[1], BACKWARDS);
        AppendText(&textEndToStart, argv[2]);

        
      }
}


