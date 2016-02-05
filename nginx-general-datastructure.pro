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
    ngx_time.c \
    ngx_linux_config.c \
    src/ngx_alloc.c \
    src/ngx_linux_config.c \
    src/ngx_log.c \
    src/ngx_palloc.c \
    src/ngx_string.c \
    src/ngx_time.c \
    src/ngx_times.c \
    test/test_ngx_sprintf.c \
    test/test_ngx_palloc.c \
    src/ngx_list.c \
    test/test_ngx_list.c \
    src/ngx_queue.c \
    test/test_ngx_queue.c \
    src/ngx_array.c \
    test/test_ngx_array.c

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
    ngx_times.h \
    ngx_auto_config.h \
    src/ngx_alloc.h \
    src/ngx_atomic.h \
    src/ngx_auto_config.h \
    src/ngx_buf.h \
    src/ngx_conf_file.h \
    src/ngx_config.h \
    src/ngx_core.h \
    src/ngx_file.h \
    src/ngx_files.h \
    src/ngx_linux_config.h \
    src/ngx_log.h \
    src/ngx_palloc.h \
    src/ngx_process.h \
    src/ngx_rbtree.h \
    src/ngx_string.h \
    src/ngx_time.h \
    src/ngx_times.h \
    src/ngx_list.h \
    src/ngx_queue.h \
    src/ngx_array.h

DISTFILES += \
    ReadMe

OTHER_FILES += \
    ReadMe

