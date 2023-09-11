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
        Text txt1 = {};
        Text txt2 = {};
  
        CreateText(&txt1, argv[1], FORWARDS);
        AppendText(&txt1, argv[2]);

        CreateText(&txt2, argv[1], BACKWARDS);
        AppendText(&txt2, argv[2]);

        // CreateText(&txt2, argv[1]);
        // AppendText(&txt2, argv[2]);
      }
}


