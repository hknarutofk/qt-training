QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base64imagedialog.cpp \
    base64imageutil.cpp \
    dialog.cpp \
    downloaddialog.cpp \
    fileiodialog.cpp \
    httputil.cpp \
    main.cpp \
    mainwindow.cpp \
    openssldialog.cpp \
    passwddialog.cpp \
    processdialog.cpp \
    debpkginstaller.cpp \
    memoryutil.cpp \
    pkexecexecutor.cpp \
    singleton.cpp \
    updater.cpp \
    textprogressbar.cpp \
    downloadmanager.cpp

HEADERS += \
    base64imagedialog.h \
    base64imageutil.h \
    dialog.h \
    downloaddialog.h \
    fileiodialog.h \
    httputil.h \
    mainwindow.h \
    openssldialog.h \
    passwddialog.h \
    processdialog.h \
    debpkginstaller.h \
    log.h \
    memoryutil.h \
    pkexecexecutor.h \
    singleton.h \
    updater.h \
    textprogressbar.h \
    downloadmanager.h

FORMS += \
    base64imagedialog.ui \
    dialog.ui \
    downloaddialog.ui \
    fileiodialog.ui \
    mainwindow.ui \
    openssldialog.ui \
    passwddialog.ui \
    processdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -lcrypto
