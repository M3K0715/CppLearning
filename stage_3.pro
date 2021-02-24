QT       += core gui serialport network  multimedia multimediawidgets


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
    camera_widget.cpp \
    enterdialog.cpp \
    local_camera.cpp \
    main.cpp \
    mainwidget.cpp \
    netwidget.cpp \
    opencv_local_camera.cpp \
    tcpclientform.cpp \
    tcpserverform.cpp \
    uart_widget.cpp \
    udp_mode.cpp

HEADERS += \
    camera_widget.h \
    enterdialog.h \
    local_camera.h \
    mainwidget.h \
    netwidget.h \
    opencv_local_camera.h \
    tcpclientform.h \
    tcpserverform.h \
    uart_widget.h \
    udp_mode.h

FORMS += \
    camera_widget.ui \
    enterdialog.ui \
    local_camera.ui \
    mainwidget.ui \
    netwidget.ui \
    opencv_local_camera.ui \
    tcpclientform.ui \
    tcpserverform.ui \
    uart_widget.ui \
    udp_mode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ico.qrc



INCLUDEPATH+=C:/Tool/OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib/include \
              C:/Tool/OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib/include/opencv \
              C:/Tool/OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib/include/opencv2

LIBS+=C:/Tool/OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib/x64/mingw/lib/libopencv_*.a

INCLUDEPATH+=C:/Tool/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include \
               C:/Tool/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include/opencv \
                C:/Tool/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include/opencv2

LIBS+=C:/Tool/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/x64/mingw/lib/libopencv_*.a
