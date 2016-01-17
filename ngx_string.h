#ifndef NGX_STRING_H
#define NGX_STRING_H
#include "ngx_config.h"
#include "ngx_core.h"
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

#define ngx_string(str) {sizeof(str) - 1,(u_char*)(str)}
#define ngx_memcpy(dst,src,n) (void) memcpy(dst,src,n)
#define ngx_cpymem(dst,src,n) (((u_char *) memcpy(dst,src,n)) + (n))

/*
 * msvc and icc7 compile memset() to the inline "rep stos"
 * while ZeroMemory() and bzero() are the calls.
 * icc7 may also inline several mov's of a zeroed register for small blocks.
 */
#define ngx_memzero(buf,n) (void)memset(buf,0,n)

u_char * ngx_cdecl ngx_sprintf(u_char *buf,const char *fmt,...);
u_char * ngx_vslprintf(u_char *buf,u_char * last,const char *fmt,va_list args);
static u_char * ngx_sprintf_num(u_char * buf,u_char *last,u_int64_t ui64,u_char zero, ngx_uint_t hexademical,ngx_uint_t width);


#endif // NGX_STRING_H

