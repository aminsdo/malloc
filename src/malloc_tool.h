#ifndef MALLOC_TOOL_H
#define MALLOC_TOOL_H

#include <stddef.h>
#include <unistd.h>

#define PAGE_SIZE sysconf(_SC_PAGE_SIZE)

void *cst(void *dat, long oft);
void *my_get_page(size_t size);
size_t align(size_t size);
size_t align_page(size_t size);
void my_memcpy(void *dst, void *src, size_t size);

#endif /* ! MALLOC_TOOL_H */
