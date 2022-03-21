#ifndef WEIRD_MEMORY_H
#define WEIRD_MEMORY_H

#include <stddef.h>

extern int g_mallocSuccess;

void*   my_malloc(size_t size);
void    manipulate();

#endif
