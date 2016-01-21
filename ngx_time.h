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

//tm_sec tm_min tm_hour ...is defined in struct tm in fiel time.h
#define ngx_tm_sec tm_sec
#define ngx_tm_min tm_min
#define ngx_tm_hour tm_hour
#define ngx_tm_mday tm_mday
#define ngx_tm_mon tm_mon
#define ngx_tm_year tm_year
#define ngx_tm_wday tm_wday
#define ngx_tm_isdst tm_isdst

#define ngx_tm_sec_t int
#define ngx_tm_min_t int
#define ngx_tm_hour_t int
#define ngx_tm_mday_t int
#define ngx_tm_mon_t int
#define ngx_tm_year_t int
#define ngx_tm_wday_t int

#if (NGX_HAVE_GMTOFF)
#define ngx_tm_gmtoff tm_gmtoff
#define ngx_tm_zone tm_zone
#endif

#if (NGX_SOLARIS)
#define ngx_timezone (isdst) (- (isdst ? altzone : timezone) / 60)
#else
#define ngx_timezone (isdst) (- (isdst? timezone + 3600 : timezone) / 60)
#endif
void ngx_localtime(time_t s,ngx_tm_t *tm);

#define ngx_gettimeofday(tp) (void) gettimeofday(tp,NULL)
#endif // NGX_TIME_H

