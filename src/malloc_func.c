#include "malloc.h"

static struct chunk *set_first_chunk(struct chunk *e, size_t size)
{
    e->next = NULL;
    e->prev = NULL;
    e->size = size - sizeof(struct chunk) - sizeof(struct mpage);
    e->state = 0;
    return e;
}

static struct chunk *get_space_chunk(struct chunk *c, size_t size)
{
    while (c && (c->state || c->size < size))
        c = c->next;
    return c;
}

void *page_add(struct mpage *p, long int size)
{
    struct chunk *e;
    char isfirst = 0;

    if (!p)
        isfirst = 1;
    p = my_get_page(size);
    if (!p)
        return NULL;
    p->state = size > PAGE_SIZE;
    p->size = size; /// align page
    p->next = NULL;
    p->prev = NULL;
    e = set_first_chunk(cst(p + 1, 0), size);
    if (isfirst)
        mplist = p;
    else
    {
        p->prev = NULL;
        p->next = mplist;
        mplist = p;
        p->next->prev = p;
    }
    return e;
}

void *get_space(struct mpage *p, size_t size)
{
    struct chunk *res = NULL;

    if (!p)
        return NULL;
    if (p->state)
        return get_space(p->next, size);
    res = get_space_chunk(cst(p + 1, 0), size);
    return ((res) ? res : get_space(p->next, size));
}

void set_chunk(struct chunk *e, size_t size)
{
    struct chunk *nxt;
    size_t cp = e->size;

    e->state = 1;
    e->size = size;
    if (cp - size >= sizeof(struct chunk) + sizeof(size_t))
    {
        nxt = cst(e + 1, size);
        nxt->prev = e;
        nxt->next = e->next;
        e->next = nxt;
        nxt->state = 0;
        nxt->size = cp - size - sizeof(struct chunk);
    }
    else
        e->size = cp;
}
