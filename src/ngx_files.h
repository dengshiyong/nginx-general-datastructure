#ifndef NGX_FILES_H
#define NGX_FILES_H
//open function defined in fcntl.h
#include <fcntl.h>
#include "ngx_core.h"
//this file exists in the os/unix direcory
//typedef int ngx_fd_t;
//
//typedef struct stat ngx_file_info_t;

#define NGX_INVALID_FILE -1
#define NGX_FILE_ERROR -1
#define ngx_open_file(name,mode,create,access) open ((const char*)name,mode | create,access)
#define ngx_open_file_n "open()"
#define ngx_close_file close
#define ngx_close_file_n "close()"
#define ngx_delete_file(name)　unlink((const char *)name)
#define ngx_delete_file_n "unlink()"
#define NGX_FILE_CREATE_OR_OPEN O_CREAT
#define NGX_FILE_APPEND (O_WRONLY | O_APPEND)
#define NGX_FILE_DEFAULT_ACCESS 0644
#define ngx_path_separator(c) ((c) == '/')
#endif // NGX_FILES_H

