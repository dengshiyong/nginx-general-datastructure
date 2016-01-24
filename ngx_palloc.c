#include "ngx_core.h"
static void * ngx_palloc_block(ngx_pool_t *pool,size_t size);
static void *ngx_palloc_large (ngx_pool_t *pool,size_t size);

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

void ngx_reset_pool (ngx_pool_t *pool){
    ngx_pool_t *p;
    ngx_pool_large_t *l;

    for (l = pool->large;l;l = l->next){
        if (l->alloc){
            ngx_free(l->alloc);
        }
    }

    for (p = pool;p;p = p->d.next){
        p->d.last = (u_char *)p + sizeof(ngx_pool_t);
        p->d.failed = 0;
    }

    pool->current = pool;
    pool->chain = NULL;
    pool->large = NULL;
}

void * ngx_palloc (ngx_pool_t *pool,size_t size){
    u_char *m;
    ngx_pool_t *p;

    if (size < pool->max){
        p = pool->current;

        do {
            m = ngx_align_ptr(p->d.last,NGX_ALIGNMENT);

            if ((size_t) (p->d.end -m) >= size){
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;
        } while (p);

        return ngx_palloc_block (pool,size);
    }
    return ngx_palloc_large (pool,size);
}

void * ngx_pnalloc (ngx_pool_t *pool,size_t size){
    u_char *m;
    ngx_pool_t *p;
    if(size <= pool->max){
        p = pool->current;

        do {
            m = p->d.last;

            if ((size_t)(p->d.end -m) >= size){
                p->d.last = m + size;
                return m;
            }
             p = p->d.next;
        }while (p);
        return ngx_palloc_block(pool,size);
    }
    return ngx_palloc_large (pool,size);
}

static void * ngx_palloc_block(ngx_pool_t *pool,size_t size){
    u_char *m;
    size_t psize;
    ngx_pool_t *p,*new;

    psize = (size_t)(pool->d.end - (u_char *)pool);

}
















































