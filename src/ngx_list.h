#ifndef NGX_LIST_H
#define NGX_LIST_H
#include "ngx_core.h"

typedef struct ngx_list_part_s ngx_list_part_t;

struct ngx_list_part_s {
   void * elts;
   ngx_uint_t nelts;
   ngx_list_part_t *next;
};

typedef struct {
    ngx_list_part_t part;
    size_t size;
    ngx_uint_t nalloc;
    ngx_pool_t *pool;
    ngx_list_part_t *last;
} ngx_list_t;

static ngx_inline ngx_int_t
ngx_list_init(ngx_list_t *list,ngx_pool_t *pool,ngx_uint_t n,size_t size){
    list->part.elts = ngx_palloc(pool,n * size);
    if (list->part.elts == NULL){
        return NGX_ERROR;
    }
    list->nalloc = n;
    list->size = size;
    list->pool = pool;
    list->part.nelts = 0;
    list->part.next = NULL;
    list->last = &list->part;

    return NGX_OK;
}

ngx_list_t *ngx_list_create(ngx_pool_t *pool,ngx_uint_t n,size_t size);

void *ngx_list_push(ngx_list_t *list);

#endif // NGX_LIST_H

