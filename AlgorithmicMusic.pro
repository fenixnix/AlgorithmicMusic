#-------------------------------------------------
#
# Project created by QtCreator 2018-05-16T16:50:11
#
#-------------------------------------------------

QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlgorithmicMusic
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ACM/algomuse.cpp \
    ACM/ntune.cpp \
    ACM/nmotivictune.cpp \
    ACM/nMidi.cpp \
    ACM/nMidiTrack.cpp \
    ACM/nTonic.cpp \
    ACM/nChord.cpp \
    ACM/algomuse.cpp \
    ACM/nchord.cpp \
    ACM/nMidi.cpp \
    ACM/nmiditrack.cpp \
    ACM/nmotivictune.cpp \
    ACM/ntonic.cpp \
    ACM/ntune.cpp \
    Device/nchiptune.cpp \
    Device/NQWavplayer.cpp \
    Device/qmusicinstrument.cpp \
    Chiptune/nmuse.cpp \
    Chiptune/nwavwriter.cpp \
    Chiptune/Sfx8Bit.cpp \
    Chiptune/wavbase.cpp \
    Chiptune/wavcontour.cpp \
    Chiptune/wavenvelope.cpp \
    Chiptune/wavfilter.cpp \
    dialogmusicinstrumenttest.cpp \
    formkeyboard.cpp \
    dialogsfx.cpp

HEADERS += \
        mainwindow.h \
    ACM/algomuse.h \
    ACM/pitchdefine.h \
    ACM/mozartdicetable.h \
    ACM/ntune.h \
    ACM/nmotivictune.h \
    ACM/percussionsound.h \
    ACM/nMidi.h \
    ACM/nMidiTrack.h \
    ACM/ntunemode.h \
    ACM/nTonic.h \
    ACM/nChord.h \
    ACM/algomuse.h \
    ACM/mozartdicetable.h \
    ACM/nchord.h \
    ACM/nMidi.h \
    ACM/nMidiTrack.h \
    ACM/nmotivictune.h \
    ACM/ntonic.h \
    ACM/ntune.h \
    ACM/ntunemode.h \
    ACM/percussionsound.h \
    ACM/pitchdefine.h \
    Device/nchiptune.h \
    Device/NQWavPlayer.h \
    Device/qmusicinstrument.h \
    Chiptune/nmuse.h \
    Chiptune/nwavwriter.h \
    Chiptune/Sfx8Bit.h \
    Chiptune/wavbase.h \
    Chiptune/wavcontour.h \
    Chiptune/wavenvelope.h \
    Chiptune/wavfilter.h \
    dialogmusicinstrumenttest.h \
    formkeyboard.h \
    dialogsfx.h

FORMS += \
        mainwindow.ui \
    dialogmusicinstrumenttest.ui \
    formkeyboard.ui \
    dialogsfx.ui

RESOURCES += \
    resource.qrc
