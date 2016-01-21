#ifndef NGX_TIMES_H
#define NGX_TIMES_H
#include "ngx_core.h"
typedef struct {
    time_t sec;
    ngx_uint_t msec;
    ngx_int_t gmtoff;
}ngx_time_t;
void ngx_gmtime(time_t t,ngx_tm_t *tp);
void ngx_time_init (void);
void ngx_time_update(void);
extern volatile ngx_str_t ngx_cached_err_log_time;
#endif // NGX_TIMES_H

