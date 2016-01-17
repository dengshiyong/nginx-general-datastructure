#ifndef NGX_CORE_H
#define NGX_CORE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ngx_config.h"
#include "ngx_rbtree.h"
#include "ngx_string.h"
#include "ngx_time.h"
#include "ngx_process.h"
#include "ngx_atomic.h"
#include "ngx_linux_config.h"

#define CR (u_char)'\r'
#define LF (u_char)'\n'
#define ngx_min(var1,var2) ((var1 > var2)?(var2):(var1))
#endif // NGX_CORE_H

