#include "memoryutil.h"
#include <stdio.h>

MemoryUtil::MemoryUtil()
{

}

void MemoryUtil::printHexDump(const char *buffer, long len)
{
    if (buffer == NULL || len <= 0)
    {
        return;
    }
    printf("0x%x: (len=%d)[", buffer, len);
    for (long i = 0; i < len; i++)
    {
        printf("%.2X ", (unsigned char)buffer[i]);
    }
    printf("]\n");
}
