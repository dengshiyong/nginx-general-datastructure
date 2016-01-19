#include "ngx_core.h"
static ngx_atomic_t ngx_time_lock;

volatile ngx_msec_t ngx_current_msec;
volatile ngx_str_t ngx_cached_err_log_time;

void ngx_time_init(void){
    ngx_cached_err_log_time.len = sizeof("1970/09/28 12:00:00") - 1;
    ngx_time_update();
}
void ngx_time_update(){
    u_char *p0,*p1;
    ngx_tm_t tm,gmt;
    time_t sec;
    ngx_uint_t msec;
    ngx_time_t *tp;
    struct timeval tv;

    if(!ngx_trylock(&ngx_time_lock)){
        return;
    }

    ngx_gettimeofday(&tv);

    sec = tv.tv_sec;
    msec = tv.tv_usec / 1000;
    ngx_current_msec = (ngx_msec_t) sec * 1000 + msec;
}
