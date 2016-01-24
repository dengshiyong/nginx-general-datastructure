#include "ngx_core.h"

ngx_pool_t * ngx_create_pool (size_t size,ngx_log_t *log){
    ngx_pool_t *p;
    p = ngx_memalign(NGX_POOL_ALIGNMENT,size,log);
    if (p == NULL){
        return NULL;
    }

}
