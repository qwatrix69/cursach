QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    complex_elements/multiplexer.cpp \
    drawer.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    simple_elements/and.cpp \
    simple_elements/buffer.cpp \
    simple_elements/invertor.cpp \
    simple_elements/nand.cpp \
    simple_elements/nor.cpp \
    simple_elements/or.cpp \
    simple_elements/xnor.cpp \
    simple_elements/xor.cpp \
    truth_table_window.cpp

HEADERS += \
    complex_elements/multiplexer.h \
    drawer.h \
    mainwindow.h \
    parser.h \
    simple_elements/and.h \
    simple_elements/buffer.h \
    simple_elements/invertor.h \
    simple_elements/nand.h \
    simple_elements/nor.h \
    simple_elements/or.h \
    simple_elements/xnor.h \
    simple_elements/xor.h \
    truth_table_window.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
