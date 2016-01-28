// gcc -o test_ngx_palloc../src/*.c -I ../src/
// ./test_ngx_palloc
#include "src/ngx_core.h"
int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;
    ngx_pool_t * pool;
    ngx_pagesize = getpagesize();
    n =  ngx_strerror_init();
    if (n == NGX_ERROR){
        return NGX_ERROR;
    }
    ngx_time_init();
    log =  ngx_log_init((u_char *)"./");
    ngx_use_stderr = 0;
    if (log == NULL){
        ngx_log_stderr(NGX_ERROR,(const char*)"can not init log ");
        return NGX_ERROR;
    }

    //test create pool
    pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE,log);
    if (pool == NULL){
        ngx_log_error(NGX_LOG_ALERT,NGX_ERROR,"can not create pool");
        return NULL;
    }

    //test log
    ngx_log_error(NGX_LOG_ALERT,NGX_OK,
                  "the pool end is: \"%s\" ",pool->d.end);

    //test destroy pool
   ngx_destroy_pool(pool);

   return NGX_OK;
}

