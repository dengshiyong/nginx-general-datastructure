// gcc -o test_ngx_array ../src/*.c  test_ngx_array.c -I ../src/
// mkdir -v logs
// cd logs
// touch error.log
// cd ..
// ./test_ngx_array

#include "../src/ngx_core.h"


typedef struct{
    u_char *str;
    ngx_queue_t queue;
    int num;
}test_node;


int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;
    ngx_pool_t *pool;
    ngx_array_t *array;
    test_node *ele_node;
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

    pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE,log);
    if (pool == NULL){
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not create pool");
        return NULL;
    }

    array = ngx_array_create(pool,1,sizeof(test_node));
    if(array == NULL){
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not create array");
        return NULL;
    }

    ele_node = ngx_array_push(array);
    if(ele_node == NULL){
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not push array");
        return NULL;
    }
    ele_node->num = 1;
    ele_node = ngx_array_push(array);
    if(ele_node == NULL){
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not push array");
        return NULL;
    }
    ele_node->num = 2;
    printf("the first value is %d\n,the second value is %d\n",
           ((test_node *)array->elts)->num,((test_node*)array->elts + 1)->num);
    ngx_array_destroy(array);
    ngx_destroy_pool(pool);

     return NGX_OK;
}
