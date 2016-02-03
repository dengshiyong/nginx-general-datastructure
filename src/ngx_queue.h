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


#endif // NGX_QUEUE_H

