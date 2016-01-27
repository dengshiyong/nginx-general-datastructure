// gcc -o test_ngx_palloc../src/*.c -I ../src/
// ./test_ngx_palloc
#include "src/ngx_core.h"
int main(int argc, char *argv[])
{
    ngx_int_t n;
    n =  ngx_strerror_init();
    if (n )
    return 0;
}

