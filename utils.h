#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

enum ERRORS
{
    NULLPTR = 0,
};

enum CORRECTFILE
{
    INCORRECT = 0,
    CORRECT   = 1
};

#define myAssert(EXPRESSION, ERROR_CODE)                                       \
    if (!(EXPRESSION))                                                         \
      {                                                                        \
        fprintf (stderr,"%s, failed at %s:%d\n", #ERROR_CODE                   \
        , __FILE__, __LINE__);                                                 \
        exit(ERROR_CODE);                                                      \
      }


int CheckFile (const char* filename);



#endif
