TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    serveur.cpp \
    pages.cpp \
    manager.cpp \
    httprequest.cpp

HEADERS += \
    serveur.h \
    pages.h \
    manager.h \
    httprequest.h

win32:LIBS += -lwsock32
LIBS += -lpthread

