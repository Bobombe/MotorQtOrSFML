#ifndef MOTEUR2D_H
#define MOTEUR2D_H


//// ToDo reimplement
//#include "mouselistener.h"
//#include "keyboardlistener.h"
//
//#include "updatable.h"
//#include "screenmanager.h"


#include <ctime>

// Includes depending on graphic choice
#ifdef IN_QT
#include <QApplication>
#include <QGraphicsView>
#include <QElapsedTimer>

#else
#include <SFML/Graphics.hpp>
#endif

class Moteur2D
#ifndef IN_QT
#else
: public QObject
#endif

{
#ifndef IN_QT
#else
Q_OBJECT
#endif

protected:

    static Moteur2D * _instance;

    int _screenWidth;
    int _screenHeight;
    int _keyboardListenersId;
    int _mouseListenersId;
    double _lastTime;

#ifdef IN_QT
    QApplication * _app;
    QGraphicsView * _view;
    QElapsedTimer _timer;

#else
    sf::RenderWindow *_window;
    sf::Clock _clock;
#endif



    // ToDo reimplement
//
//        // Managing Textures
//        std::map<std::string, sf::Texture*> m_textures;
//        std::map<std::string, int> m_texturesUtilisations;
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
    void run();

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
//        // Pas vraiment un seleter
//        void unloadTexture(const std::string& imagePath);

/////////////////////////////////////////////////////
///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
    // ToDo reimplement
//        sf::Texture* getTexture(const std::string& imagePath);
//
//        const std::map <int, KeyboardListener*>& getKeyboardListeners();
//        const std::map <int, MouseListener*>& getMouseListeners();
//
//        sf::Time getTime();
//
//
//        ScreenManager * getScreenManager ()
//        {
//            return m_scm;
//        }
//
//        sf::Vector2i getScreenSize()
//        {
//            return m_screenSize;
//        }


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
