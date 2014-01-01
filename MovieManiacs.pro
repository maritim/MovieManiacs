#-------------------------------------------------
#
# Project created by QtCreator 2013-07-07T03:27:21
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network

TARGET = MovieManiacs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    movie.cpp \
    simpledialog.cpp \
    networkclass.cpp \
    movieform.cpp \
    actor.cpp \
    diskwriter.cpp \
    newmoviedialog.cpp \
    idget.cpp \
    samplemovie.cpp \
    partialmoviedownloader.cpp \
    moviedownloader.cpp \
    jsonparser.cpp \
    messagebox.cpp

HEADERS  += mainwindow.h \
    movie.h \
    simpledialog.h \
    networkclass.h \
    movieform.h \
    actor.h \
    diskwriter.h \
    newmoviedialog.h \
    idget.h \
    samplemovie.h \
    partialmoviedownloader.h \
    MOC_DIR \
    moviedownloader.h \
    jsonparser.h \
    moc_partialmoviedownloader.h \
    messagebox.h

FORMS    += mainwindow.ui \
    simpledialog.ui \
    movieform.ui \
    newmoviedialog.ui \
    idget.ui

RESOURCES += \
    MovieManiacsResource.qrc
