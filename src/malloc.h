#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include "malloc_tool.h"

extern struct mpage *mplist;

struct mpage
{
    char state;
    size_t size;
    struct mpage *next;
    struct mpage *prev;
};

struct chunk
{
    char state;
    size_t size;
    struct chunk *next;
    struct chunk *prev;
};

void *malloc(size_t size);
void free(void *ptr);

void *page_add(struct mpage *p, long int size);
void *get_space(struct mpage *p, size_t size);
void set_chunk(struct chunk *e, size_t size);
void free_merge(struct chunk *e);
struct chunk *realloc_resize(struct chunk *c, size_t size);
void *realloc_replace(struct chunk *c, size_t size);

#endif /* ! MALLOC_H */
