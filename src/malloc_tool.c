#define _GNU_SOURCE

#include <sys/mman.h>
#include "malloc_tool.h"

void *cst(void *dat, long oft)
{
    char *cp = dat;
    cp += oft;
    return cp;
}

void *my_get_page(size_t size)
{
    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE
                      | MAP_ANONYMOUS, 1, 0);
    if (addr == MAP_FAILED)
        return NULL;
    return addr;
}

size_t align(size_t size)
{
    if (size % sizeof(size_t))
        size += sizeof(size_t) - size % sizeof(size_t);
    return size;
}

size_t align_page(size_t size)
{
    if (size % PAGE_SIZE)
        size += PAGE_SIZE - size % PAGE_SIZE;
    return size;
}

void my_memcpy(void *dst, void *src, size_t size)
{
    char *cpd = dst;
    char *cps = src;
    for (size_t i = 0; i < size; ++i)
        cpd[i] = cps[i];
}
