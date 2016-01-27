#ifndef NGX_FILE_H
#define NGX_FILE_H
#include "ngx_core.h"


struct ngx_file_s {
    ngx_fd_t fd;
    ngx_str_t name;
    ngx_file_info_t info;

    off_t offset;
    off_t sys_offset;

    ngx_log_t *log;
    //for worked no error,I comment thest lines
//#if (NGX_THREADS)
//    ngx_int_t                (*thread_handler)(ngx_thread_task_t *task,
//                                               ngx_file_t *file);
//    void                      *thread_ctx;
//#endif
//
//#if (NGX_HAVE_FILE_AIO)
//    ngx_event_aio_t           *aio;
//#endif

    unsigned valid_info:1;
    unsigned directio:1;
};

#endif // NGX_FILE_H

