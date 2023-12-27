#include "malloc.h"

struct chunk *realloc_resize(struct chunk *c, size_t size)
{
    struct chunk *tmp;

    if (!c || !size)
        return NULL;

    tmp = c->next;
    if (!tmp)
        return NULL;
    c->next = tmp->next;
    if (c->next)
        c->next->prev = c;
    c->size += sizeof(struct chunk) + tmp->size;
    return c;
}

void *realloc_replace(struct chunk *c, size_t size)
{
    void *dat;

    if (!c || !size)
        return NULL;

    dat = malloc(size);
    if (!dat)
        return NULL;
    my_memcpy(dat, c + 1, c->size);
    free(c + 1);
    return dat;
}
