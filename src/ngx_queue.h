#ifndef NGX_QUEUE_H
#define NGX_QUEUE_H
#include "ngx_core.h"

typedef struct ngx_queue_s ngx_queue_t;
struct ngx_queue_s {
    ngx_queue_t *next;
    ngx_queue_t *prev;
};

#define ngx_hueue_init(h)    \
    (h)->prev = h;           \
    (h)->next = h

#define ngx_queue_empty(h)    \
    (h)->prev == h)

#define ngx_queue_insert_head(h,x)    \
    (x)->next = (h)->next;            \
    (x)->prev = h;                    \
    (h)->next = x;                    \
    (x)->next->prev = x

#define ngx_queue_insert_tail(h,x)     \
    (x)->prev = (h)->prev;             \
    (x)->next = h;                     \
    (x)->prev->next = x;               \
    (h)->prev = x

#define ngx_queue_head(h)               \
    (h)->next

#define ngx_queue_last(h)               \
    (h)->prev

#define ngx_queue_sentinel(h)           \
    (h)


#if(NGX_DEBUG)
#define ngx_queue_remove(x)           \
    (x)->prev->next = (x)->next;         \
    (x)->next->prev = (x)->prev;        \
    (x)->prev = NULL;                   \
    (x)->next = NULL
#else
#define ngx_queue_remove(x)           \
    (x)->prev->next = (x)->next;         \
    (x)->next->prev = (x)->prev

#endif


#define ngx_queue_split(h,q,n)                \
    (n)->prev = (h)->prev;                    \
    (n)->prev->next = n;                      \
    (n)->next = q;                            \
    (h)->prev = (q)->prev;                    \
    (q)->prev->next = h;                      \
    (q)->prev = n






#endif // NGX_QUEUE_H

