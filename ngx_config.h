#ifndef NGX_CONFIG_H
#define NGX_CONFIG_H
//just for intptr_t uintptr_t
#include <stdint.h>
#define ngx_cdecl

typedef uintptr_t ngx_uint_t;
typedef intptr_t ngx_int_t;

#define NGX_INT32_LEN (sizeof("-2147483648") - 1)
#define NGX_INT64_LEN (sizeof("-9223372036854775808") - 1)

// just for the source can work
#define NGX_PTR_SIZE  4
#if(NGX_PTR_SIZE == 4)
#define NGX_INT_T_LEN NGX_INT32_LEN
#define NGX_MAX_INT_T_VALUE 2147483647

#else
#define NGX_INT_T_LEN NGX_INT64_LEN
#define NGX_MAX_INT_T_VALUE 9223372036854775807
#endif

#ifndef NGX_ALIGNMENT
#define NGX_ALIGNMENT sizeof(unsigned long) /*platform word*/
#endif

#define ngx_align(d,a) (((d)+(a-1)) & ~(a-1))
#define ngx_align_ptr(p,a)   (u_char*) (((uintptr_t )(p) + ((uintptr_t)a - 1)) & ~ ((uintptr_t)a - 1))
#endif // NGX_CONFIG_H

