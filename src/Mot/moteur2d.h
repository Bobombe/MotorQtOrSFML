#ifndef MOTEUR2D_H
#define MOTEUR2D_H


//// ToDo reimplement
//#include "mouselistener.h"
//#include "keyboardlistener.h"
//
//#include "updatable.h"
//#include "screenmanager.h"

// cpp includes
#include <map>
#include <string>

// Motor includes
#include "Texture.h"
#include "Sprite.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Vector2d.h"

// Includes depending on graphic choice
#ifdef IN_QT
#include <QApplication>
#include <QGraphicsView>
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
    int _keyboardListenersId;
    int _mouseListenersId;
    double _lastTime;

    ScreenManager* _screenManager;


#ifdef IN_QT
    QApplication * _app;
    QGraphicsView * _view;
    QElapsedTimer _timer;

#else
    sf::RenderWindow *_window;
    sf::Clock _clock;
#endif

    // Managing Textures
    std::map<std::string, Texture*> _textures;


    // ToDo reimplement
//
//
//        // First called by eventmanager
//        std::map <int, KeyboardListener*> m_keyboardListeners;
//        std::map <int, MouseListener*> m_mouseListeners;

    // ToDo reimplement
//        ScreenManager * m_scm;
//
//
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
    // ToDo reimplement
//        void setScreenManager (ScreenManager * scm)
//        {
//            m_scm = scm;
//        }
//
//        int addKeyboardListener(KeyboardListener* kl);
//        int addMouseListener(MouseListener* ml);

/////////////////////////////////////////////////////
///////////          DELETERS             ///////////
/////////////////////////////////////////////////////

    // ToDo reimplement
//        void deleteKeyboardListener(int index);
//        void deleteMouseListener(int index);
//
        // Kind of a deleter
    void unloadTexture(const std::string& imagePath);

/////////////////////////////////////////////////////
///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
    Texture * getTexture(const std::string& imagePath);
    // ToDo reimplement
//
//        const std::map <int, KeyboardListener*>& getKeyboardListeners();
//        const std::map <int, MouseListener*>& getMouseListeners();
//
//
    ScreenManager * getScreenManager ()
    {
        return _screenManager;
    }

    Vector2d getScreenSize()
    {
        return _screenSize;
    }


    // Specific functions
#ifdef IN_QT
    QGraphicsView * getView();

#else

    sf::RenderWindow * getWindow();
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
