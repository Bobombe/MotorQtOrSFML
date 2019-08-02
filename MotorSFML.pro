TEMPLATE = app
win32:CONFIG(debug, debug|release): CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include


win32:CONFIG(release, debug|release): dlls_to_move.path = $$OUT_PWD/release
else:win32:CONFIG(debug, debug|release): dlls_to_move.path = $$OUT_PWD/debug
else:unix: dlls_to_move.path = $$OUT_PWD/release

win32:CONFIG(release, debug|release): dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-2.dll ../SFML-2.5.1/bin/sfml-system-2.dll ../SFML-2.5.1/bin/sfml-window-2.dll
else:win32:CONFIG(debug, debug|release): dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-d-2.dll ../SFML-2.5.1/bin/sfml-system-d-2.dll ../SFML-2.5.1/bin/sfml-window-d-2.dll
else:unix: dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-2.dll ../SFML-2.5.1/bin/sfml-system-2.dll ../SFML-2.5.1/bin/sfml-window-2.dll

INSTALLS += dlls_to_move
