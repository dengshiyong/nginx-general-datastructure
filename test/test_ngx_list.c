// gcc -o test_ngx_list  ../src/*.c  test_ngx_list.c -I ../src/
// mkdir -v logs
// cd logs
// touch error.log
// cd ..
// ./test_ngx_list
#include "../src/ngx_core.h"
int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;
    ngx_pool_t * pool;
    ngx_list_t *list;
    ngx_str_t *str[4];
    ngx_str_t *getstr;
    ngx_list_part_t *part;

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
        ngx_log_error(NGX_LOG_ALERT,log,NGX_ERROR,"can not create pool");
        return NULL;
    }

    //test ngx_list
    //create a list ,the ngx_list_part_t has an array which has 2 elments which is ngs_str_t
   list = ngx_list_create(pool,4,sizeof(ngx_str_t));
   if (list == NULL){
       ngx_log_error(NGX_LOG_ALERT,log,NGX_OK,"can not create a list from the pool \n");
       ngx_destroy_pool(pool);
      return NGX_ERROR;
   }

   for (n = 0;n < 4;n++){
       str[n] = ngx_list_push(list);
       if (str[n] == NULL){
           ngx_log_error(NGX_LOG_ALERT,log,NGX_OK,"can not push the str[%i]",n);
           ngx_destroy_pool(pool);
           return NGX_ERROR;
       }
   }

   str[0]->len = sizeof("the 0 string");
   str[0]->data = "the 0 string";
   str[1]->len = sizeof("the 1 string");
   str[1]->data = "the 1 string";
   str[2]->len = sizeof("the 2 string");
   str[2]->data = "the 2 string";
   str[3]->len = sizeof("the 3 string,hehe");
   str[3]->data = "the 3 string,hehe";

   part = &list->part;
   getstr = part->elts;

   for (n = 0;;n++){
       if (n >= part->nelts){
           if(part->next == NULL){
               break;
           }
           part = part->next;
           getstr = part->elts;

           n = 0;
       }
       ngx_log_error(NGX_LOG_ALERT,log,NGX_OK,"the %i str is %*s\n",n,getstr->len,getstr->data);
       getstr = part->elts + list->size * (n+1);
   }

   ngx_destroy_pool(pool);
   return NGX_OK;
}

