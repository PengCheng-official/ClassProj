QT       += core gui
QT	 += multimedia
QT       += network
QT       += charts

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

INCLUDEPATH += $$PWD/include

LIBS += -L$$PWD/lib

LIBS += -lelawidgettools

SOURCES += \
    chatmessage/qnchatmessage.cpp \
    chatroom.cpp \
    login.cpp \
    main.cpp \
    allmain.cpp \
    objects/chat.cpp \
    objects/client.cpp \
    objects/order.cpp \
    objects/orderlist.cpp \
    objects/product.cpp \
    objects/search.cpp \
    objects/shopping.cpp \
    objects/strategy.cpp \
    objecttojson.cpp \
    signin.cpp \
    ui/basepage.cpp \
    ui/homepage.cpp \
    ui/personpage.cpp \
    ui/searchpage.cpp \
    ui/shoppingpage.cpp

HEADERS += \
    allmain.h \
    chatmessage/qnchatmessage.h \
    chatroom.h \
    login.h \
    objects/chat.h \
    objects/client.h \
    objects/objects.h \
    objects/order.h \
    objects/orderlist.h \
    objects/product.h \
    objects/search.h \
    objects/shopping.h \
    objects/strategy.h \
    objecttojson.h \
    signin.h \
    statement.h \
    ui/basepage.h \
    ui/homepage.h \
    ui/personpage.h \
    ui/searchpage.h \
    ui/shoppingpage.h

FORMS += \
    allmain.ui \
    chatroom.ui \
    login.ui \
    signin.ui

RESOURCES += \
    include/ElaWidgetTools.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
