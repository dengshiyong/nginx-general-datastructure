#ifndef NGX_STRING_H
#define NGX_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include "ngx_config.h"
typedef struct {
    size_t len;
    u_char *data;
}ngx_str_t;

typedef struct {
    unsigned len:28;
    unsigned valid:1;
    unsigned no_cacheable:1;
    unsigned not_found:1;
    unsigned escape:1;

    u_char *data;
}ngx_variable_value_t;


u_char * ngx_vslprintf(u_char *buf,u_char * last,const char *fmt,va_list args);
#endif // NGX_STRING_H

