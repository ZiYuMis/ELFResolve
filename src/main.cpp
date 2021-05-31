#include <iostream>

unsigned char *buf = NULL;

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
    //for (long i = 0; i < num / 16; i++)
    for (long i = 0; i <  16; i++)
    {
        printf("%09x  :      ",i);
        for (long j = 0; j < 16; j++)
        {
            printf("%02x ", buf[i * 16 + j]);
        }
        printf("\n");
    }

    fclose(fid);
}

int main()
{
    readFile();
    free(buf); //释放内存
    std::cout << "hello world ! " << std::endl;
    return 0;
}