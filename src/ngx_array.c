#include "ngx_core.h"

ngx_array_t *
ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size)
{
    ngx_array_t *a;

    a = ngx_palloc(p, sizeof(ngx_array_t));
    if (a == NULL) {
        return NULL;
    }

    if (ngx_array_init(a, p, n, size) != NGX_OK) {
        return NULL;
    }

    return a;
}


void
ngx_array_destroy(ngx_array_t *a)
{
    ngx_pool_t  *p;

    p = a->pool;

    if ((u_char *) a->elts + a->size * a->nalloc == p->d.last) {
        p->d.last = (u_char*)a->elts;
    }

    if ((u_char *) a + sizeof(ngx_array_t) == p->d.last) {
        p->d.last = (u_char *) a;
    }
}

void *ngx_array_push(ngx_array_t *a){
    void *new ,*elt;
    if (a->nelts == a->nalloc){
        if ((u_char*)(a->elts + a->nelts * a->size) == a->pool->d.last
                && ((a->pool->d.end - a->pool->d.last) >= a->size)){
            a->nalloc++;
            a->pool->d.last += a->size;
        }
        else{
            new = ngx_palloc(a->pool,a->nalloc * 2 * a->size);
           if (new == NULL){
               return NULL;
           }
           ngx_memcpy(new,a->elts,a->nelts * a->size);
           a->elts = new;
        }
    }
    elt =  (u_char *)a->elts + a->nelts * a->size;
    a->nelts++;
   return elt;
}

void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n){
    void *new,*elt;
    ngx_pool_t *p;
    size_t size;
    ngx_uint_t nalloc;
    if(a->nelts + n > a->nalloc){
        p = a->pool;
        size = a->size * a->nalloc;
       if ((u_char *)a->elts + size == p->d.last
                && p->d.end - p->d.last >= a->size * n){
            p->d.last += a->size * n;
            a->nalloc += n;
        }
        else{
           nalloc = 2* ((n < a->nalloc)?a->nalloc : n ) ;
           new = ngx_palloc(p,a->size * nalloc);
           if (new == NULL){
               return NULL;
           }
           ngx_memcpy(new,a->elts,size);
           a->elts = new;
           a->nalloc = nalloc;
       }
    }
    elt = (u_char *) a->elts + a->nelts * a->size;
    a->nelts += n;
    return elt;
}






















