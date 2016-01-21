#include "ngx_core.h"
void ngx_localtime(time_t s, ngx_tm_t *tm){
#if (NGX_HAVE_LOCALTIME_R)
    (void) localtime_r(&s,tm);
#else
    struct tm *t;

    t = localtime(&s);
    *tm = *t;
#endif
}
