#include "weird_memory.h"
#include "rd_route/rd_route.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void* (*real_malloc)(size_t);
ssize_t (*real_write)(int, const void*, size_t);
int g_mallocSuccess = 1;

void* my_malloc(size_t size)
{
    if (g_mallocSuccess == 0)
        return (NULL);
    return real_malloc(size);
}

ssize_t my_write(int fd, const void* buf, size_t len)
{
    ssize_t ret = 0;


    if (fd != 2)
        return real_write(fd, buf, len);
    ssize_t ret = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (i % 2 == 0)
        {
            ssize_t r = real_write(fd, &buf[i], 1);
            if (r < 0)
                return r;
            ret += r;
        }
    }
    return ret;
}

void install() __attribute__ ((constructor));

void install()
{
    rd_route(malloc, my_malloc, (void **)&real_malloc);
    rd_route(write, my_write, (void **)&real_write);
    printf("Manipulated functions\n");
}
