TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ngx_string.c \
    test_ngx_sprintf.c \
    ngx_palloc.c \
    ngx_alloc.c \
    ngx_log.c \
    ngx_times.c \
    ngx_time.c

include(deployment.pri)
qtcAddDeployment()
INCLUDEPATH += . \
        /usr/lib/gcc/x86_64-linux-gnu/4.8/include/
HEADERS += \
    ngx_string.h \
    ngx_config.h \
    ngx_core.h \
    ngx_rbtree.h \
    ngx_time.h \
    ngx_process.h \
    ngx_atomic.h \
    ngx_linux_config.h \
    ngx_palloc.h \
    ngx_buf.h \
    ngx_file.h \
    ngx_files.h \
    ngx_log.h \
    ngx_conf_file.h \
    ngx_alloc.h \
    ngx_errno.h \
    ngx_times.h \
    ngx_auto_config.h

