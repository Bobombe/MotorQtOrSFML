TEMPLATE = app
win32:CONFIG(debug, debug|release): CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_parallel_to_source

SOURCES += \
    LD45/BaseAnimatedSprite.cpp \
    LD45/BaseCharacter.cpp \
    LD45/Equipment.cpp \
    LD45/Level.cpp \
    LD45/Player.cpp \
    LD45/ScreenManagerLD45.cpp \
    LD45/TitleScreen.cpp \
    TU/Main.cpp \
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
    src/TestGravity.cpp \
    TU/ScreenManagerTest.cpp \
    TU/TitleScreen.cpp \
    MotorSources/AnimatedSprite.cpp \
    MotorSources/Button.cpp \
    MotorSources/Camera.cpp \
    MotorSources/Collider.cpp \
    MotorSources/EventsManager.cpp \
    MotorSources/Force.cpp \
    MotorSources/KeyboardListener.cpp \
    MotorSources/moteur2d.cpp \
    MotorSources/MouseAndKeyListener.cpp \
    MotorSources/MouseListener.cpp \
    MotorSources/Obstacle.cpp \
    MotorSources/Rectangle.cpp \
    MotorSources/Screen.cpp \
    MotorSources/ScreenManager.cpp \
    MotorSources/Sprite.cpp \
    MotorSources/Text.cpp \
    MotorSources/Texture.cpp \
    MotorSources/Vector2d.cpp \
    MotorSources/WorldElement.cpp \
    MotorSources/Sound.cpp

HEADERS += \
    LD45/BaseAnimatedSprite.h \
    LD45/BaseCharacter.h \
    LD45/Equipment.h \
    LD45/Level.h \
    LD45/Player.h \
    LD45/ScreenManagerLD45.h \
    LD45/TitleScreen.h \
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
    TU/ScreenManagerTest.h \
    TU/TitleScreen.h \
    MotorSources/AnimatedSprite.h \
    MotorSources/Button.h \
    MotorSources/Camera.h \
    MotorSources/Collider.h \
    MotorSources/EventsManager.h \
    MotorSources/Force.h \
    MotorSources/KeyboardListener.h \
    MotorSources/moteur2d.h \
    MotorSources/MouseAndKeyListener.h \
    MotorSources/MouseListener.h \
    MotorSources/Obstacle.h \
    MotorSources/Rectangle.h \
    MotorSources/Screen.h \
    MotorSources/ScreenManager.h \
    MotorSources/Sprite.h \
    MotorSources/Text.h \
    MotorSources/Texture.h \
    MotorSources/Vector2d.h \
    MotorSources/WorldElement.h \
    MotorSources/Sound.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-audio-d
else:unix: LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-audio

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
INCLUDEPATH += MotorSources
DEPENDPATH += $$PWD/../SFML-2.5.1/include

# Copy dlls
win32:CONFIG(release, debug|release): dlls_to_move.path = $$OUT_PWD/release
else:win32:CONFIG(debug, debug|release): dlls_to_move.path = $$OUT_PWD/debug
else:unix: dlls_to_move.path = $$OUT_PWD/release

win32:CONFIG(release, debug|release): dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-2.dll ../SFML-2.5.1/bin/sfml-system-2.dll ../SFML-2.5.1/bin/sfml-window-2.dll ../SFML-2.5.1/bin/sfml-audio-2.dll ../SFML-2.5.1/bin/openal32.dll
else:win32:CONFIG(debug, debug|release): dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-d-2.dll ../SFML-2.5.1/bin/sfml-system-d-2.dll ../SFML-2.5.1/bin/sfml-window-d-2.dll ../SFML-2.5.1/bin/sfml-audio-d-2.dll ../SFML-2.5.1/bin/openal32.dll
else:unix: dlls_to_move.files += ../SFML-2.5.1/bin/sfml-graphics-2.dll ../SFML-2.5.1/bin/sfml-system-2.dll ../SFML-2.5.1/bin/sfml-window-2.dll ../SFML-2.5.1/bin/sfml-audio-2.dll ../SFML-2.5.1/bin/openal32.dll

INSTALLS += dlls_to_move

# Copy ressources
win32:CONFIG(release, debug|release): ressources.path = $$OUT_PWD/release
else:win32:CONFIG(debug, debug|release): ressources.path = $$OUT_PWD/debug
else:unix: ressources.path = $$OUT_PWD/release

ressources.files += TU/Ressources MotorSources/MotorResources LD45/Ressources

INSTALLS += dlls_to_move ressources
