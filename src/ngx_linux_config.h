#ifndef NGX_LINUX_CONFIG_H
#define NGX_LINUX_CONFIG_H
#include <sys/resource.h>
#include <sys/stat.h>
//unistd.h　defined the getpid() write () function
#include <unistd.h>
#include "ngx_core.h"
//the next 3 lines is os/unix/ngx_errno.h under nginx-1.8.0
typedef int ngx_err_t;
#define NGX_ENOSPC ENOSPC
#define NGX_ENOENT ENOENT
#define ngx_errno errno

//the next two  functions defined in os/unix/ngx_errno.h .c under nginx-1.8.0
u_char * ngx_strerror(ngx_err_t err,u_char *errstr,size_t size);
ngx_int_t ngx_strerror_init(void);

//NGX_TID_T_FMT is defined in os/unix/ngx_thread.h
#define NGX_TID_T_FMT  "%d"
// the extern variant is defined in /os/unix/ngx_process.h
//extern ngx_pid_t ngx_pid;
//the next 1 line is defined in os/unix/ngx_process.h
#define ngx_get_pid getpid
//#ifndef ngx_log_pid
//#define ngx_log_pid  ngx_pid
//#endif
// the next  lines until line #define NGX_LINEFEED_SIZE 1 are defined in os/unix/ngx_files.h
/*
 * we use inlined function instead of simple #define
 * because glibc 2.3 sets warn_unused_result attribute for write()
 * and in this case gcc 4.3 ignores (void) cast
 */
static ngx_inline ssize_t ngx_write_fd (ngx_fd_t fd,void *buf,size_t n){
    return write (fd,buf,n);
}

#define ngx_write_console ngx_write_fd
#define ngx_linefeed(p) *p++ = LF;
#define NGX_LINEFEED_SIZE 1
#define ngx_stderr STDERR_FILENO
#endif // NGX_LINUX_CONFIG_H

