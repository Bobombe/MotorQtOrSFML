TEMPLATE = app
win32:CONFIG(debug, debug|release): CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_parallel_to_source

SOURCES += \
    GenericPlatformer/GPCamera.cpp \
    GenericPlatformer/GPCharacter.cpp \
    GenericPlatformer/GPGravity.cpp \
    GenericPlatformer/GPScreen.cpp \
    GenericPlatformer/GPScreenManager.cpp \
    LD40/Dephazor.cpp \
    LD40/GameManager.cpp \
    LD40/GameOverButton.cpp \
    LD40/Opponent.cpp \
    LD40/Planet.cpp \
    LD40/Pod.cpp \
    LD40/ScreenLevel1.cpp \
    LD40/Spaceship.cpp \
    LD40/StartScreenLD40.cpp \
    LD45/BaseAnimatedSprite.cpp \
    LD45/BaseCharacter.cpp \
    LD45/Equipment.cpp \
    LD45/Level.cpp \
    LD45/Player.cpp \
    LD45/ScreenManagerLD45.cpp \
    LD45/TitleScreen.cpp \
    LD46/CompanioBall.cpp \
    LD46/LD46ScreenManager.cpp \
    LD46/LD46TitleScreen.cpp \
    LD46/Level1.cpp \
    LD46/MetalBackSprite.cpp \
    LD46/Platform.cpp \
    LD46/SadRobot.cpp \
    LD46/WallSprites.cpp \
    Launcher/LauncherScreen.cpp \
    Launcher/LauncherScreenManager.cpp \
    Launcher/Main.cpp \
    TU/Main.cpp \
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
    GenericPlatformer/GPCamera.h \
    GenericPlatformer/GPCharacter.h \
    GenericPlatformer/GPGravity.h \
    GenericPlatformer/GPScreen.h \
    GenericPlatformer/GPScreenManager.h \
    LD40/Dephazor.h \
    LD40/GameManager.h \
    LD40/GameOverButton.h \
    LD40/Opponent.h \
    LD40/Planet.h \
    LD40/Pod.h \
    LD40/ScreenLevel1.h \
    LD40/Spaceship.h \
    LD40/StartScreenLD40.h \
    LD45/BaseAnimatedSprite.h \
    LD45/BaseCharacter.h \
    LD45/Equipment.h \
    LD45/Level.h \
    LD45/Player.h \
    LD45/ScreenManagerLD45.h \
    LD45/TitleScreen.h \
    LD46/CompanioBall.h \
    LD46/LD46ScreenManager.h \
    LD46/LD46TitleScreen.h \
    LD46/Level1.h \
    LD46/MetalBackSprite.h \
    LD46/Platform.h \
    LD46/SadRobot.h \
    LD46/WallSprites.h \
    Launcher/LauncherScreen.h \
    Launcher/LauncherScreenManager.h \
    MotorSources/Color.h \
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

ressources.files += TU/Ressources MotorSources/MotorResources LD40/Ressources LD45/Ressources LD46/Ressources Launcher/Ressources

INSTALLS += dlls_to_move ressources
