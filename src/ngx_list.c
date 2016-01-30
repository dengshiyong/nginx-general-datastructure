#include "ngx_core.h"


ngx_list_t *ngx_list_create(ngx_pool_t *pool, ngx_uint_t n, size_t size){
   ngx_list_t *l;
   l = ngx_palloc(pool,sizeof(ngx_list_t));
   if (l == NULL){
       return NULL;
   }
   if (ngx_list_init(l,pool,n,size) != NGX_OK){
       return NULL;
   }
   return l;
}


void *ngx_list_push(ngx_list_t *list){
    ngx_list_part_t *lp;
    if (list->nalloc > list->last->nelts){
        list->last->nelts ++;
        return (list->last->elts + list->size);
    }
    lp = ngx_pcalloc(list->pool,sizeof(ngx_list_part_t));
    if (lp == NULL){
        return NULL;
    }
    lp->elts = ngx_pcalloc(list->pool,list->nalloc * list->size);
    if (lp->elts == NULL){
        return NULL;
    }
    lp->next = NULL;
    lp->nelts = 0;
    list->last->next = lp;
    return lp->elts;
}





















