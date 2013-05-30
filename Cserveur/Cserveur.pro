TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    serveur.cpp \
    pages.cpp \
    manager.cpp \
    httpanswer.cpp \
    parser.cpp \
    httpquery.cpp \
    fileprocessing.cpp

HEADERS += \
    serveur.h \
    pages.h \
    manager.h \
    httpanswer.h \
    parser.h \
    httpquery.h \
    fileprocessing.h

win32:LIBS += -lwsock32
LIBS += -lpthread

