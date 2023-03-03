QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += C:\apps\opencv\release\install\include

LIBS += C:\apps\opencv\release\bin\libopencv_core460.dll
LIBS += C:\apps\opencv\release\bin\libopencv_highgui460.dll
LIBS += C:\apps\opencv\release\bin\libopencv_imgcodecs460.dll
LIBS += C:\apps\opencv\release\bin\libopencv_imgproc460.dll
LIBS += C:\apps\opencv\release\bin\libopencv_calib3d460.dll
LIBS += C:\apps\opencv\release\bin\libopencv_calib3d460.dll

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Filters/convolution.cpp \
    Filters/gaussian.cpp \
    Filters/prewitt.cpp \
    Filters/robert.cpp \
    Filters/sobel.cpp \
    Noise/noise.cpp \
    Noise/remove_noise.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Common.hpp \
    Filters/convolution.hpp \
    Filters/gaussian.hpp \
    Filters/prewitt.hpp \
    Filters/robert.hpp \
    Filters/sobel.hpp \
    Noise/noise.hpp \
    Noise/remove_noise.hpp \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
