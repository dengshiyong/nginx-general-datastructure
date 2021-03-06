//this file exists in the os/unix directory
#ifndef NGX_ALLOC_H
#define NGX_ALLOC_H
#include "ngx_core.h"
void *ngx_alloc (size_t size,ngx_log_t *log);

#define ngx_free free
/*
 * Linux has memalign() or posix_memalign()
 * Solaris has memalign()
 * FreeBSD 7.0 has posix_memalign(), besides, early version's malloc()
 * aligns allocations bigger than page size at the page boundary
 */

#if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)

void *ngx_memalign(size_t alignment,size_t size,ngx_log_t *log);

#else
#define ngx_memalign(alignment,size,log) ngx_alloc(size,log)
#endif

extern ngx_uint_t ngx_pagesize;
#endif // NGX_ALLOC_H

