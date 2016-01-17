#ifndef NGX_ATOMIC_H
#define NGX_ATOMIC_H
#include "ngx_core.h"
typedef int64_t ngx_atomic_int_t;
typedef u_int64_t ngx_atomic_uint_t;
#define NGX_ATOMIC_T_LEN (sizeof("-9223372036854775808")-1)
#endif // NGX_ATOMIC_H

