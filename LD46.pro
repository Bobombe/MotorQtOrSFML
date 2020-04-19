TEMPLATE = app
win32:CONFIG(debug, debug|release): CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_parallel_to_source

SOURCES += \
    LD46/Main.cpp \
    LD46/ScreenManagerTest.cpp \
    LD46/TitleScreen.cpp \
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
    MotorSources/Sound.cpp \
    LD46/Level1.cpp \
    LD46/WallSprites.cpp \
    LD46/MetalBackSprite.cpp \
    LD46/Platform.cpp \
    LD46/SadRobot.cpp \
    LD46/CompanioBall.cpp

HEADERS += \
    LD46/ScreenManagerTest.h \
    LD46/TitleScreen.h \
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
    MotorSources/Sound.h \
    LD46/Level1.h \
    LD46/WallSprites.h \
    LD46/MetalBackSprite.h \
    LD46/Platform.h \
    LD46/SadRobot.h \
    LD46/CompanioBall.h

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

# Add std libs
MINGWBIN = $$(QTDIR)/bin
dlls_to_move.files += ../SFML-2.5.1/license.md $$MINGWBIN/libgcc_s_dw2-1.dll $$MINGWBIN/libstdc++-6.dll $$MINGWBIN/libwinpthread-1.dll

INSTALLS += dlls_to_move

# Copy ressources
win32:CONFIG(release, debug|release): ressources.path = $$OUT_PWD/release
else:win32:CONFIG(debug, debug|release): ressources.path = $$OUT_PWD/debug
else:unix: ressources.path = $$OUT_PWD/release

ressources.files += MotorSources/MotorResources LD46/Ressources

INSTALLS += dlls_to_move ressources

#win32:CONFIG(release, debug|release): QMAKE_CLEAN += $$OUT_PWD/release/LD46 $$OUT_PWD/release/MotorSources
#else:win32:CONFIG(debug, debug|release): QMAKE_CLEAN += $$OUT_PWD/debug/LD46 $$OUT_PWD/debug/MotorSources
#else:unix: QMAKE_CLEAN += "$$OUT_PWD/release/LD46 /Q" "$$OUT_PWD/release/MotorSources /Q"
