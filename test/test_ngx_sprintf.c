// gcc -o test_ngx_sprintf ../src/*.c -I ../src/
//./test_ngx_sprintf
#include "../src/ngx_core.h"
int main (){
    char buf[30];
    ngx_memzero(buf,sizeof(buf));
   // ngx_str_t * teststring = malloc(sizeof(ngx_str_t));
   // teststring->data = "hello world";
   // teststring->len = sizeof("helloworld");
    ngx_str_t teststring = ngx_string("hello world");
    ngx_str_t welcomestring = ngx_string("welcome");
    ngx_sprintf(buf,"%V and %V", &teststring,&welcomestring);
    printf ("the buf is %s\n",buf);
   return 0;
}
