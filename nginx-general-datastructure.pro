TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ngx_string.c \
    test_ngx_sprintf.c

include(deployment.pri)
qtcAddDeployment()
INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/4.8/include/
HEADERS += \
    ngx_string.h \
    ngx_config.h \
    ngx_core.h \
    ngx_rbtree.h \
    ngx_time.h \
    ngx_process.h \
    ngx_atomic.h \
    ngx_linux_config.h

