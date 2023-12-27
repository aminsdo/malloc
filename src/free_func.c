#include <sys/mman.h>
#include "malloc.h"

static void free_page(struct mpage *p)
{
    if (!p)
        return;
    if (!p->prev)
    {
        mplist = p->next;
        if (mplist)
        {
            mplist->prev = NULL;
            if (mplist->next)
                mplist->next->prev = mplist;
        }
    }
    else
    {
        p->prev->next = p->next;
        if (p->next)
            p->next->prev = p->prev;
    }
    munmap(p, p->size);
}

static void free_page_check(struct chunk *e)
{
    struct mpage *p = cst(e, 0);

    if (!p)
        return;
    --p;
    if (e->size >= PAGE_SIZE - sizeof(struct chunk) - sizeof(struct mpage))
        if (e->size == p->size - sizeof(struct mpage) - sizeof(struct chunk))
            free_page(p);
}

static void merge_next(struct chunk *e)
{
    struct chunk *tmp;

    if (!e->next)
        return;
    tmp = e->next;
    e->next = tmp->next;
    if (e->next)
        e->next->prev = e;
    e->size += tmp->size + sizeof(struct chunk);
}

void free_merge(struct chunk *e)
{
    if (!e)
        return;

    if (e->next && !e->next->state)
        merge_next(e);
    free_page_check(e);
}
