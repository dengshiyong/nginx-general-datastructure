#ifndef NGX_ATOMIC_H
#define NGX_ATOMIC_H
#include "ngx_core.h"
typedef int64_t ngx_atomic_int_t;
typedef u_int64_t ngx_atomic_uint_t;
typedef volatile ngx_atomic_uint_t ngx_atomic_t;
#define NGX_ATOMIC_T_LEN (sizeof("-9223372036854775808")-1)
//ngx_atomic_cmp_set ngx_memory_barrier　exists in the file ngx_gcc_atomic_amd64.h ngx_gcc_atomic....h　and so on
//to guarantee the source can worked correctly ,I move them here
#if (NGX_SMP)
#define NGX_SMP_LOCK "lock;"
#else
#define NGX_SMP_LOCK
#endif
static ngx_inline ngx_atomic_uint_t ngx_atomic_cmp_set (ngx_atomic_t  *lock,ngx_atomic_uint_t old,ngx_atomic_uint_t set){
    u_char res;

// the asm volatile means it's an asm code
// NGX_SMP_LOCK in x86 amd64 machine means "lock;"
// the "lock;" stand for the dB level of bus will be sent to 0,and the cpu can not visit the memory through the bus
// cmpxchgq %3,%1 means change the value of %3 parameter(which means "set" which is in the register(r means register))
//and %1 parameter(which means "lock" which is in the memory ("m" means it is in memory)
//sete set the the file %0 parameter(which means "res","=a"means it is the output )
//when zf == 1,then res = 1,else res = 0
    __asm__ volatile (

                NGX_SMP_LOCK
                "  cmpxchgq %3,%1;  "
                "  sete %0;  "

                : "=a"(res):"m"(*lock),"a"(old),"r"(set):"cc","memory");
    return res;
}
#define ngx_memory_barrier() __asm__ volatile ("" ::: "memory")
//that's all
#define ngx_trylock(llock) (*(llock) == 0 && ngx_atomic_cmp_set (llock,0,1))
#define ngx_unlock(llock) *(llock) = 0
#endif // NGX_ATOMIC_H

