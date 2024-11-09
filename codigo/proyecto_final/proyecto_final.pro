QT       += core gui  multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    public/audios/main_theme.mp3 \
    public/images/Imagen_promocional_4F02.webp \
    public/images/genesis_tub.png \
    public/images/map_base_KrustyLand.png \
    resources/audios/main_theme.mp3 \
    resources/images/Imagen_promocional_4F02.webp \
    resources/images/genesis_tub.png