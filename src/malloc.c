#include "malloc.h"

struct mpage *mplist = NULL;

__attribute__((visibility("default")))
void *malloc(size_t size)
{
    size_t psize;
    struct chunk *new;

    if (!size)
        return NULL;
    size = align(size);
    if (size > PAGE_SIZE - sizeof(struct mpage) - sizeof(struct chunk))
    {
        psize = align_page(size + sizeof(struct mpage) + sizeof(struct chunk));
        new = page_add(mplist, psize);
        if (!new)
            return NULL;
    }
    else
        new = get_space(mplist, size);
    if (!new)
        new = page_add(mplist, PAGE_SIZE);
    if (!new)
        return NULL;
    set_chunk(new, size);

    return (new + 1);
}

__attribute__((visibility("default")))
void free(void *ptr)
{
    struct chunk *e = ptr;

    if (!e)
        return;
    --e;
    e->state = 0;
    free_merge(e);
}

__attribute__((visibility("default")))
void *realloc(void *ptr, size_t size)
{
    struct chunk *c = ptr;

    if (!ptr)
        return malloc(size);
    if (!size)
    {
        free(ptr);
        return NULL;
    }
    size = align(size);
    --c;
    if (size > c->size)
    {
        if (c->next && !c->next->state
            && c->next->size + sizeof(struct chunk) + c->size >= size)
            c = realloc_resize(c, size);
        else
            return realloc_replace(c, size);
    }
    if (!c)
        return NULL;
    set_chunk(c, size);

    return (c + 1);
}

__attribute__((visibility("default")))
void *calloc(size_t  nmemb, size_t size)
{
    char *dat = malloc(size * nmemb);
    size_t len = size * nmemb;
    for (size_t i = 0; i < len; ++i)
        dat[i] = 0;
    return dat;
}
