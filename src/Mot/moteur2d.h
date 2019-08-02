#ifndef MOTEUR2D_H
#define MOTEUR2D_H
#include <sstream>

#define STOI( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

//// ToDo reimplement
//#include "mouselistener.h"
//#include "keyboardlistener.h"
//
//#include "updatable.h"
//#include "screenmanager.h"

// cpp includes
#include <map>
#include <vector>
#include <string>

// Motor includes
#include "Texture.h"
#include "Sprite.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Vector2d.h"
#include "EventsManager.h"
#include "KeyboardListener.h"
#include "MouseListener.h"

// Includes depending on graphic choice
#ifdef IN_QT
#include <QApplication>
#include <QElapsedTimer>

#else
#include <SFML/Graphics.hpp>
#endif

class Moteur2D
#ifdef IN_QT
: public QObject
#endif

{
#ifdef IN_QT
Q_OBJECT
#endif

protected:

    static Moteur2D * _instance;

    Vector2d _screenSize;
    double _lastTime;

    ScreenManager* _screenManager;

    EventsManager * _eventsManager;

    // Managing Textures
    std::map<std::string, Texture*> _textures;

    // First called by eventmanager
    std::map <int, KeyboardListener*> _keyboardListeners;
    int _keyboardListenersId;
    std::map <int, MouseListener*> _mouseListeners;
    int _mouseListenersId;

#ifdef IN_QT
    QApplication * _app;
    QElapsedTimer _timer;

#else
    sf::RenderWindow *_window;
    sf::Clock _clock;
    sf::Font _font;
#endif

public:
    static Moteur2D* getInstance();

/////////////////////////////////////////////////////
///////////          METHODES             ///////////
/////////////////////////////////////////////////////
    void init(int width, int height, std::string windowName, int argc, char **argv);
    void run(ScreenManager* screenManager);

    double getMsSinceLaunch();

/////////////////////////////////////////////////////
///////////           ADDERS              ///////////
/////////////////////////////////////////////////////
    int addKeyboardListener(KeyboardListener* kl);
    int addMouseListener(MouseListener* ml);

/////////////////////////////////////////////////////
///////////          DELETERS             ///////////
/////////////////////////////////////////////////////
    void deleteKeyboardListener(int index);
    void deleteMouseListener(int index);

        // Kind of a deleter
    void unloadTexture(const std::string& imagePath);

/////////////////////////////////////////////////////
///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
    Texture * getTexture(const std::string& imagePath);
    const std::map <int, KeyboardListener*>& getKeyboardListeners();
    const std::map <int, MouseListener*>& getMouseListeners();

    ScreenManager * getScreenManager ()
    {
        return _screenManager;
    }

    Vector2d getScreenSize()
    {
        return _screenSize;
    }

    Screen* getCurrentScreen();
    int getCurrentScreenId();


    // Specific functions
#ifdef IN_QT
    QWidget * getView();

#else

    sf::RenderWindow * getWindow();
    sf::Font & getFont();
    sf::Font & setFont(std::string fontPath);
#endif


#ifdef IN_QT
public slots:
#endif
    // Called 60 times per seconds
    void update();

private:
    Moteur2D();
    virtual ~Moteur2D();
};

#endif // MOTEUR2D_H
