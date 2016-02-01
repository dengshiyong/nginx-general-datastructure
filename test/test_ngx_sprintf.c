// gcc -o test_ngx_sprintf ../src/*.c  test_ngx_sprintf.c -I ../src/
// mkdir -v logs
// cd logs
// touch error.log
// cd ..
// ./test_ngx_sprintf
#include "../src/ngx_core.h"
int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;
    ngx_pool_t * pool;
    char buf[30];
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
//    ngx_log_stderr(NGX_ERROR,(const char*)"nima");

    //test create pool
    pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE,log);
    if (pool == NULL){
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not create pool");
        return NULL;
    }
     ngx_memzero(buf,sizeof(buf));
    ngx_str_t teststring = ngx_string("hello world");
    ngx_str_t welcomestring = ngx_string("welcome");
    ngx_slprintf(buf,buf+NGX_MAX_ERROR_STR,"%V and %V",&teststring,&welcomestring);
    ngx_sprintf(buf,"%V and %V", &teststring,&welcomestring);
    printf ("the buf is %s\n",buf);
    printf ("the address of buf is  %p\n",buf);
    printf ("the address of last is %p\n",buf+NGX_MAX_ERROR_STR);

    //test destroy pool
   ngx_destroy_pool(pool);

   return NGX_OK;
}
