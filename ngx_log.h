#ifndef NGX_LOG_H
#define NGX_LOG_H
#include "ngx_core.h"

#define NGX_LOG_DEBUG 8
typedef u_char * (*ngx_log_handler_pt) (ngx_log_t *log,u_char *buf,size_t len);
typedef void (*ngx_log_writer_pt) (ngx_log_t *log,ngx_uint_t level,u_char * buf,size_t len);

struct ngx_log_s {
    ngx_uint_t log_level;
    ngx_open_file_t *file;

    ngx_atomic_uint_t connection;

    time_t disk_full_time;

    ngx_log_handler_pt handler;
    void *data;

    ngx_log_writer_pt writer;
    void *wdata;

     /*
     * we declare "action" as "char *" because the actions are usually
     * the static strings and in the "u_char *" case we have to override
     * their types all the time
     */

    char *action;

    ngx_log_t *next;
};
/*********************************/
#if (NGX_HAVE_C99_VARIADIC_MACROS)
#define NGX_HAVE_VARIADIC_MACROS 1
#define ngx_log_error (level,log,...) if ((log)->log_level >= level) ngx_log_error_core (level,log,_VA_ARGS_)

void ngx_log_error_core (ngx_uint_t level,ngx_log_t *log,ngx_err_t err,const char *fmt,...);

#define ngx_log_debug (level,log,...) if ((log)->log_level & level) ngx_log_error_core (NGX_LOG_DEBUG,log,_VA_ARGS_)

/*********************************/


/*********************************/

#endif // NGX_LOG_H
