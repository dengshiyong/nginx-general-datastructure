#ifndef NGX_CORE_H
#define NGX_CORE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// string.h defined the strerror function
#include <string.h>
//errno.h defined the errno macro
#include <errno.h>
//stddef.h defined offsetof macro
#include <stddef.h>
typedef struct ngx_pool_s ngx_pool_t;
typedef struct ngx_chain_s ngx_chain_t;
typedef struct ngx_file_s ngx_file_t;
typedef struct ngx_log_s ngx_log_t;
typedef struct ngx_open_file_s ngx_open_file_t;


#define NGX_OK 0
#define NGX_ERROR -1
#define NGX_DECLINED -5

#include "ngx_config.h"
#include "ngx_rbtree.h"
#include "ngx_string.h"
#include "ngx_time.h"
#include "ngx_process.h"
#include "ngx_atomic.h"
#include "ngx_linux_config.h"
#include "ngx_palloc.h"
#include "ngx_buf.h"
#include "ngx_file.h"
#include "ngx_files.h"
#include "ngx_log.h"
#include "ngx_conf_file.h"
#include "ngx_alloc.h"
#include "ngx_times.h"
#include "ngx_auto_config.h"
#include "ngx_list.h"
#include "ngx_queue.h"
#include "ngx_array.h"

#define CR (u_char)'\r'
#define LF (u_char)'\n'
#define ngx_min(var1,var2) ((var1 > var2)?(var2):(var1))
#endif // NGX_CORE_H

