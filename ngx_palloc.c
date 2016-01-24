#include "ngx_core.h"

ngx_pool_t * ngx_create_pool (size_t size,ngx_log_t *log){
    ngx_pool_t *p;
    p = ngx_memalign(NGX_POOL_ALIGNMENT,size,log);
    if (p == NULL){
        return NULL;
    }
    p->d.last = (u_char *)p + sizeof(ngx_pool_t);
    p->d.end = (u_char *)p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_t);
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL)?size:NGX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    p->chain = NULL;
    p->large = NULL;
    p->cleanup = NULL;
    p->log = log;

    return p;
}

void ngx_destroy_pool (ngx_pool_t *pool){
    ngx_pool_t *p,*n;
    ngx_pool_large_t *l;
    ngx_pool_cleanup_t *c;

   for (c = pool->cleanup;c;c = c->next){
       if (c->handler){
           c->handler(c->data);
       }
   }

    for (l = pool->large;l;l = l->next){
        if (l->alloc){
            ngx_free(l->alloc);
        }
    }

   for (p = pool,n = pool->d.next;/*void*/;p = n,n = n->d.next){
       ngx_free(p);

       if (n == NULL){
           break;
       }
   }
}





















































