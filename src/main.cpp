#include <iostream>
#include "../include/ElfSolve.h"

unsigned char *buf = NULL;
unsigned char* pBufIndex = NULL;




int main()
{
    readFile();
    solveElfHeader();


    free(buf); //ιζΎεε­
    return 0;
}