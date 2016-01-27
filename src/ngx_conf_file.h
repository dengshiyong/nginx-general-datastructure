#ifndef NGX_CONF_FILE_H
#define NGX_CONF_FILE_H
#include "ngx_core.h"

struct ngx_open_file_s {
    ngx_fd_t fd;
    ngx_str_t name;

    void (*flush) (ngx_open_file_t *file,ngx_log_t *log);
    void *data;
};

#endif // NGX_CONF_FILE_H

