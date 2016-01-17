//this file exists in the os/unix directory
#include "ngx_alloc.h"

void * ngx_alloc (size_t size, ngx_log_t *log){
    void *p;
    p = malloc(size);
    if (p == NULL){
        ngx_log_error
    }
}
