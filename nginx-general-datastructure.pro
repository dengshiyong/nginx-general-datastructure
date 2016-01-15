TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    ngx_string.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ngx_string.h \
    ngx_config.h \
    ngx_core.h \
    ngx_rbtree.h \
    ngx_time.h

