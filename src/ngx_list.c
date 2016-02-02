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
    void *elts;
    ngx_list_part_t *lp;
    lp = list->last;
    if (list->nalloc == list->last->nelts){
        lp = ngx_palloc(list->pool,sizeof(ngx_list_part_t));
        if (lp == NULL){
            return NULL;
        }
        lp->elts = ngx_palloc(list->pool,list->nalloc * list->size);
        if (lp->elts == NULL){
            return NULL;
        }
        lp->next = NULL;
        lp->nelts = 0;
        list->last->next = lp;
        list->last = lp;
    }
    elts = (char *)lp->elts + list->size * lp->nelts;
    lp->nelts ++;
    return elts;
}





















