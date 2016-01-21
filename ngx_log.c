#include "ngx_core.h"
#if (NGX_HAVE_VARIADIC_MACROS)

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...){

#else

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, va_list args){

#endif
#if (NGX_HAVE_VARIADIC_MACROS)
    va_list args;
#endif
    u_char *p,*last,*msg;
    ssize_t n;
    ngx_uint_t wrote_stderr,debug_connection;
    u_char errstr[NGX_MAX_ERROR_STR];
    last = errstr + NGX_MAX_ERROR_STR;
    //it seems do not set the ngx_cached_err_log_time.len value
    p = ngx_cpymem(errstr,ngx_cached_err_log_time.data,
                   ngx_cached_err_log_time.len);
    p = ngx_sl
}
