// gcc -o test_ngx_palloc../src/*.c -I ../src/
// ./test_ngx_palloc
#include "src/ngx_core.h"
int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;
    n =  ngx_strerror_init();
    if (n == NGX_ERROR){
        return NGX_ERROR;
    }
    ngx_time_init();
    log =  ngx_log_init((u_char *))

}

