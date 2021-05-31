#include "../include/ElfSolve.h"
#include <iostream>

void readFile()
{
    FILE *fid;
    fid = fopen("/bin/readelf", "rb");
    if (fid == NULL)
    {
        printf("读取文件出错");
        return;
    }
    int mode = 1;

    //获取文件大小
    fseek(fid, 0, SEEK_END);
    long lSize = ftell(fid);
    rewind(fid);
    //开辟存储空间
    long num = lSize / sizeof(char);
    buf = (unsigned char *)malloc(sizeof(unsigned char) * num);
    if (buf == NULL)
    {
        printf("开辟空间出错");
        return;
    }
    fread(buf, sizeof(unsigned char), num, fid);

    fclose(fid);
}

void printFile()
{
    //for (long i = 0; i < num / 16; i++)
    for (long i = 0; i < 16; i++)
    {
        printf("%09x  :      ", i);
        for (long j = 0; j < 16; j++)
        {
            printf("%02x ", buf[i * 16 + j]);
        }
        printf("\n");
    }
}

void solveElfHeader()
{
    pBufIndex = buf;
    Elf32_Ehdr *pElfHeader = (Elf32_Ehdr *)pBufIndex;
    pBufIndex += sizeof(Elf32_Ehdr);
    printf("==========================ELF HEADER========================================\n");
    printf("EI_NIDENT:      ");
    for(int i = 0;i<EI_NIDENT;i++)
    {
        printf("%02x ",pElfHeader->e_ident[i]);
    }
    printf("\n");

    printf("Magic :         %c%c%c%c  \n", pElfHeader->e_ident[0], pElfHeader->e_ident[1], pElfHeader->e_ident[2], pElfHeader->e_ident[3]);

    switch (pElfHeader->e_ident[EI_CLASS])
    {
    case ELFCLASSNONE:
        printf("Class :         Invalid class\n");
        break;
    case ELFCLASS32:
        printf("Class :         32-bit objects\n");
        break;
    case ELFCLASS64:
        printf("Class :         64-bit objects\n");
        break;
    default:
        printf("Class :         Invalid class\n");
        break;
    }

    switch (pElfHeader->e_ident[EI_DATA])
    {
    case ELFDATANONE:
        printf("Data :          Invalid class\n");
        break;
    case ELFDATA2LSB:
        printf("Data :          2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("Data :          2's complement, big endian\n");
        break;
    default:
        printf("Data :         Invalid class\n");
        break;
    }

    printf("Version :       %X\n", pElfHeader->e_ident[EI_VERSION]);

    switch (pElfHeader->e_ident[EI_OSABI])
    {

    case ELFOSABI_NONE:
        printf("OS/ABI :       	UNIX System V ABI\n");
        break;

    case ELFOSABI_HPUX:
        printf("OS/ABI :       	HP-UX\n");
        break;
    case ELFOSABI_NETBSD:
        printf("OS/ABI :       	NetBSD\n");
        break;
    case ELFOSABI_GNU:
        printf("OS/ABI :       	GNU ELF extensions\n");
        break;
    case ELFOSABI_SOLARIS:
        printf("OS/ABI :       	Sun Solaris\n");
        break;
    case ELFOSABI_AIX:
        printf("OS/ABI :       	IBM AIX\n");
        break;
    case ELFOSABI_IRIX:
        printf("OS/ABI :       	SGI Irix.\n");
        break;
    case ELFOSABI_FREEBSD:
        printf("OS/ABI :       	FreeBSD\n");
        break;
    case ELFOSABI_TRU64:
        printf("OS/ABI :       	Compaq TRU64 UNIX\n");
        break;
    case ELFOSABI_MODESTO:
        printf("OS/ABI :       	Novell Modesto\n");
        break;
    case ELFOSABI_OPENBSD:
        printf("OS/ABI :       	OpenBSD\n");
        break;
    case ELFOSABI_ARM_AEABI:
        printf("OS/ABI :       	ARM EABI\n");
        break;
    case ELFOSABI_ARM:
        printf("OS/ABI :       	ARM\n");
        break;
    case ELFOSABI_STANDALONE:
        printf("OS/ABI :       	Standalone (embedded) application\n");
        break;
    }

    printf("ABI Version:    %02x\n",pElfHeader->e_ident[EI_ABIVERSION]);

    printf("======================================================================\n");
}