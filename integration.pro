QT       += core gui sql multimedia multimediawidgets printsupport charts serialport svg network
QT+=axcontainer
QT       += core gui  serialport
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
    Dataset.cpp \
    Personnel.cpp \
    Stat.cpp \
    Weights.cpp \
    arduino.cpp \
    chatserver.cpp \
    chatsocket.cpp \
    connection.cpp \
    dumessengerconnectiondialog.cpp \
    envoiefactureparmail.cpp \
    exel.cpp \
    facture.cpp \
    logement.cpp \
    main.cpp \
    mainwindow.cpp \
    notification.cpp \
    participant.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    spectateurs.cpp \
    sport.cpp \
    terrain.cpp \
    test.cpp \
    utils.cpp

HEADERS += \
    Dataset.h \
    LinearRegressionModel.h \
    Personnel.h \
    Stat.h \
    Weights.h \
    arduino.h \
    chatserver.h \
    chatsocket.h \
    connection.h \
    dumessengerconnectiondialog.h \
    envoiefactureparmail.h \
    exel.h \
    facture.h \
    logement.h \
    mainwindow.h \
    notification.h \
    participant.h \
    qcustomplot.h \
    qrcode.h \
    spectateurs.h \
    sport.h \
    terrain.h \
    test.h \
    utils.h

FORMS += \
    Stat.ui \
    dumessengerconnectiondialog.ui \
    form.ui \
    personnel.ui\
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
