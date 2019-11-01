#-------------------------------------------------
#
# Project created by QtCreator 2019-10-08T22:32:03
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookStudy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Http/HttpRequest.cpp \
        Http/LoginWithQQMail.cpp \
        LoginDialog.cpp \
        Model/BookModel.cpp \
        Model/UserModel.cpp \
        Utility/Utility.cpp \
        Widgets/AvatorWidget.cpp \
        Widgets/BookViewWidget.cpp \
        Widgets/BookWidget.cpp \
        Widgets/CategoryWidget.cpp \
        Widgets/PromptWidget.cpp \
        Widgets/UserPageWidget.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Http/HttpRequest.h \
        Http/ILoginOperation.h \
        Http/LoginWithQQMail.h \
        LoginDialog.h \
        MainWindow.h \
        Model/BookModel.h \
        Model/UserModel.h \
        Utility/BookStudyAPI.h \
        Utility/Utility.h \
        Widgets/AvatorWidget.h \
        Widgets/BookViewWidget.h \
        Widgets/BookWidget.h \
        Widgets/CategoryWidget.h \
        Widgets/PromptWidget.h \
        Widgets/UserPageWidget.h

FORMS += \
        LoginDialog.ui \
        MainWindow.ui \
        Widgets/CategoryWidget.ui \
        Widgets/UserPageWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Assets/Resource.qrc
