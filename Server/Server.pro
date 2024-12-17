QT       += core gui
QT	 += multimedia
QT       += network
QT       += charts
QT       += sql

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
    ThreadPool.cpp \
    chatmessage/qnchatmessage.cpp \
    chatroom.cpp \
    dao/chatmapper.cpp \
    dao/clientmapper.cpp \
    dao/mapper.cpp \
    dao/orderlistmapper.cpp \
    dao/ordermapper.cpp \
    dao/productmapper.cpp \
    dao/shoppingmapper.cpp \
    main.cpp \
    allmain.cpp \
    objects/chat.cpp \
    objects/client.cpp \
    objects/order.cpp \
    objects/orderlist.cpp \
    objects/product.cpp \
    objects/search.cpp \
    objects/shopping.cpp \
    objecttojson.cpp \
    ui/basepage.cpp \
    ui/chatpage.cpp \
    ui/historypage.cpp \
    ui/homepage.cpp \
    ui/productpage.cpp \
    ui/searchpage.cpp

HEADERS += \
    ThreadPool.h \
    allmain.h \
    chatmessage/qnchatmessage.h \
    chatroom.h \
    dao/chatmapper.h \
    dao/clientmapper.h \
    dao/mapper.h \
    dao/orderlistmapper.h \
    dao/ordermapper.h \
    dao/productmapper.h \
    dao/shoppingmapper.h \
    objects/chat.h \
    objects/client.h \
    objects/objects.h \
    objects/order.h \
    objects/orderlist.h \
    objects/product.h \
    objects/search.h \
    objects/shopping.h \
    objecttojson.h \
    statement.h \
    ui/basepage.h \
    ui/chatpage.h \
    ui/historypage.h \
    ui/homepage.h \
    ui/productpage.h \
    ui/searchpage.h

FORMS += \
    allmain.ui \
    chatroom.ui

RESOURCES += \
    include/ElaWidgetTools.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

