#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "weird_memory.h"

int main(void)
{
    for (int i = 0; i < 10; ++i)
    {
        g_mallocSuccess = i != 5;

        char* mem = malloc(16);
        if (mem == NULL)
            write(2, "NULL!!\n", 7);
        else
        {
            strlcpy(mem, "Worked!", 16);
            write(2, mem, 7);
            write(2, "\n", 1);
            free(mem);
        }
    }
    return (0);
}
