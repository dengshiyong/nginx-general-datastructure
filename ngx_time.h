//this file exists in os/unix directory in nginx
#ifndef NGX_TIME_H
#define NGX_TIME_H
//for the struct tm should include time.h
//but time.h is included in sys/time.h
//#include <time.h>
//for gettimeofday
#include <sys/time.h>
#include "ngx_core.h"
typedef ngx_rbtree_key_t ngx_msec_t;
typedef ngx_rbtree_key_int_t ngx_msec_int_t;

typedef struct tm ngx_tm_t;
#define ngx_gettimeofday(tp) (void) gettimeofday(tp,NULL)
#endif // NGX_TIME_H

