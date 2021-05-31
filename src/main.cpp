#include <iostream>
#include "../include/ElfSolve.h"

unsigned char *buf = NULL;
unsigned char* pBufIndex = NULL;




int main()
{
    readFile();
    solveElfHeader();


    free(buf); //释放内存
    return 0;
}