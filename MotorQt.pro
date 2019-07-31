#-------------------------------------------------
#
# Project created by QtCreator 2019-07-29T18:01:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotorQtOrSFML
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += IN_QT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/Dephazor.cpp \
    src/GameManager.cpp \
    src/GameOverButton.cpp \
    src/LifeGameScreen.cpp \
    src/Opponent.cpp \
    src/PersoTest.cpp \
    src/Planet.cpp \
    src/Pod.cpp \
    src/ScreenLevel1.cpp \
    src/Spaceship.cpp \
    src/StartScreen.cpp \
    src/StartScreenLD40.cpp \
    src/Test.cpp \
    src/TestGravity.cpp \
    src/TU/ScreenManagerTest.cpp \
    src/TU/TitleScreen.cpp \
    src/Mot/AnimatedSprite.cpp \
    src/Mot/Button.cpp \
    src/Mot/Camera.cpp \
    src/Mot/Collider.cpp \
    src/Mot/EventsManager.cpp \
    src/Mot/Force.cpp \
    src/Mot/KeyboardListener.cpp \
    src/Mot/moteur2d.cpp \
    src/Mot/MouseAndKeyListener.cpp \
    src/Mot/MouseListener.cpp \
    src/Mot/Obstacle.cpp \
    src/Mot/Rectangle.cpp \
    src/Mot/Screen.cpp \
    src/Mot/ScreenManager.cpp \
    src/Mot/Sprite.cpp \
    src/Mot/Text.cpp \
    src/Mot/Texture.cpp \
    src/Mot/Vector2d.cpp \
    src/Mot/WorldElement.cpp

HEADERS += \
    src/Dephazor.h \
    src/GameManager.h \
    src/GameOverButton.h \
    src/LifeGameScreen.h \
    src/Opponent.h \
    src/PersoTest.h \
    src/Planet.h \
    src/Pod.h \
    src/ScreenLevel1.h \
    src/Spaceship.h \
    src/StartScreen.h \
    src/StartScreenLD40.h \
    src/TestGravity.h \
    src/TU/ScreenManagerTest.h \
    src/TU/TitleScreen.h \
    src/Mot/AnimatedSprite.h \
    src/Mot/Button.h \
    src/Mot/Camera.h \
    src/Mot/Collider.h \
    src/Mot/EventsManager.h \
    src/Mot/Force.h \
    src/Mot/KeyboardListener.h \
    src/Mot/moteur2d.h \
    src/Mot/MouseAndKeyListener.h \
    src/Mot/MouseListener.h \
    src/Mot/Obstacle.h \
    src/Mot/Rectangle.h \
    src/Mot/Screen.h \
    src/Mot/ScreenManager.h \
    src/Mot/Sprite.h \
    src/Mot/Text.h \
    src/Mot/Texture.h \
    src/Mot/Vector2d.h \
    src/Mot/WorldElement.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
