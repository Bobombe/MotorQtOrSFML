
#include "moteur2d.h"
#include <stdexcept>
#include <iostream>


// ToDo reimplement
//

#ifndef IN_QT
#include "eventmanager.h"
#else
#include <QTimer>
#endif

Moteur2D * Moteur2D::_instance = 0;

Moteur2D * Moteur2D::getInstance()
{
    if (_instance == 0)
    {
        _instance = new Moteur2D();
    }
    return _instance;
}

Moteur2D::Moteur2D() : _screenWidth(0), _screenHeight(0), _keyboardListenersId(0), _mouseListenersId(0), _lastTime(0),
#ifndef IN_QT
        _window(0)
#else
        _app(0), _view(0)
#endif
{
    //ctor
}

Moteur2D::~Moteur2D()
{
    //dtor
    std::cout << "dest Moteur2D " << this << std::endl;
    // TO DO : revoir le destructeur
    if(_instance)
        delete _instance;

#ifndef IN_QT
    if (_window) {
        delete _window;
    }
#else
    if (_app) {
        delete _app;
    }
    if (_view) {
        delete _view;
    }

#endif
}


  /////////////////////////////////////////////////////
 ///////////          METHODES             ///////////
/////////////////////////////////////////////////////

void Moteur2D::init(int width, int height, std::string windowName, int argc, char **argv)
{
#ifdef IN_QT
    _app = new QApplication(argc, argv);
    _view = new QGraphicsView();
    _view->setFixedWidth(width);
    _view->setFixedHeight(height);
    _view->show();
    _timer.start();

#else

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    _window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Default, settings);
#endif

    _screenWidth = width;
    _screenHeight = height;
}

void Moteur2D::run()
{

    _lastTime = getMsSinceLaunch();
#ifdef IN_QT
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60);

    _app->exec();

#else

    EventManager em;
    sf::Time t1 = _clock.getElapsedTime();
    sf::Time t2;
    float s = 0;
    _window->setVerticalSyncEnabled(true);

    while(_window->isOpen())
    {
        // TO DO : Relacher le proc
        // Attente active
        while (s<1/60.)
        {
            t2 = _clock.getElapsedTime();
            s = (t2-t1).asSeconds() ;
        }

        update();

        t1 = t2;
    }
#endif
}

double Moteur2D::getMsSinceLaunch()
{
#ifdef IN_QT
    return _timer.elapsed();
#else
    return _clock.getElapsedTime().asMilliseconds();
#endif
}



void Moteur2D::update()
{
    double curTime = getMsSinceLaunch();
    double elapsedTime = double(curTime - _lastTime) / 1000.;
    double frameRate = 1000. / double(curTime - _lastTime);
    std::cout << "RUN at " << frameRate << " frame per sec. elapsedTime = " << elapsedTime << " , curTime = " << curTime << std::endl;

    // Things to update here

#ifdef IN_QT
#else
    // Clear window
    m_window->clear();
#endif

    /*/ First called by eventmanager
    em.eventLoop(*m_window);

    if (m_scm)
        m_scm->update(s);

    if (m_scm)
        m_scm->draw();//*/

#ifdef IN_QT
#else
    // Display window
    m_window->display();
#endif
    _lastTime = curTime;

}


  /////////////////////////////////////////////////////
 ///////////           ADDERS              ///////////
/////////////////////////////////////////////////////
/* TODO sup pour ecran
int Moteur2D::addPreDrawable(sf::Sprite* s)
{
    m_preDrawablesIndex++;
    m_preDraw[m_preDrawablesIndex] = s;
    return m_preDrawablesIndex;
}
int Moteur2D::addDrawable(sf::Sprite *s)
{
    m_drawablesIndex++;
    m_drawables[m_drawablesIndex] = s;
    return m_drawablesIndex;
}
int Moteur2D::addPostDrawable(sf::Sprite* s)
{
    m_postDrawablesIndex++;
    m_postDraw[m_postDrawablesIndex] = s;
    return m_postDrawablesIndex;
}
//*/


// ToDo reimplement
//int Moteur2D::addKeyboardListener(KeyboardListener* kl)
//{
//    ++m_keyboardListenersId;
//    m_keyboardListeners[m_keyboardListenersId]=kl;
//    return m_keyboardListenersId;
//}
//int Moteur2D::addMouseListener(MouseListener* ml)
//{
//    ++m_mouseListenersId;
//    m_mouseListeners[m_mouseListenersId]=ml;
//    return m_mouseListenersId;
//}
//
//int Moteur2D::addUpdate(Updatable* upd)
//{
//    ++m_updatesId;
//    m_updates[m_updatesId]=upd;
//    return m_updatesId;
//}

  /////////////////////////////////////////////////////
 ///////////          DELETERS             ///////////
/////////////////////////////////////////////////////
/* TODO sup pour ecran
void Moteur2D::deletePreDrawable(int index)
{
    m_preDraw.erase(index);
}
void Moteur2D::deleteDrawable(int index)
{
    m_drawables.erase(index);
}
void Moteur2D::deletePostDrawable(int index)
{
    m_postDraw.erase(index);
}
//*/

// ToDo reimplement
//void Moteur2D::deleteKeyboardListener(int index)
//{
//    m_keyboardListeners.erase(index);
//}
//void Moteur2D::deleteMouseListener(int index)
//{
//    m_mouseListeners.erase(index);
//}
//
//void Moteur2D::deleteUpdate(int index)
//{
//    m_updates.erase(index);
//}
//
//void Moteur2D::unloadTexture(const std::string& imagePath)
//{
//    try
//    {
//        int val = m_texturesUtilisations.at(imagePath);
//        val--;
//        if (val <= 0) // Suppression de la texture
//        {
//            sf::Texture * t = m_textures.at(imagePath);
//            m_textures.erase(imagePath);
//            m_texturesUtilisations.erase(imagePath);
//            delete t;
//        }
//        else
//        {
//            m_texturesUtilisations.at(imagePath) = val;
//        }
//        return;
//    }
//    catch (const std::out_of_range& oor) // Ajout de la texture
//    {
//    }
//
//}

  /////////////////////////////////////////////////////
 ///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
// Permet l'acc�s aux textures, si la texture est inexistante cette methode la cr�era.
// ToDo reimplement
//sf::Texture* Moteur2D::getTexture(const std::string& imagePath)
//{
//    try
//    {
//        sf::Texture * t = m_textures.at(imagePath);
//        m_texturesUtilisations.at(imagePath) = m_texturesUtilisations.at(imagePath)+1;
//        return t;
//    }
//    catch (const std::out_of_range& oor) // Ajout de la texture
//    {
//        // Texture in�xistante, je la charge
//        sf::Texture *t = new sf::Texture();
//        if(t->loadFromFile(imagePath))
//        {
//            m_textures.insert(std::pair<std::string, sf::Texture*>(imagePath, t));
//            m_texturesUtilisations.insert(std::pair<std::string, int>(imagePath, 1));
//            return t;
//        }
//        else
//        {
//            // problem !
//            delete t;
//            std::cerr << "Probl�me d'ajout de Texture" << std::endl;
//            return 0;
//        }
//    }/* TODO : A supprimer apr�s un moment de test
//    try
//    {
//        return &m_textures.at(imagePath);
//    }
//    catch (const std::out_of_range& oor)
//    {
//        // problem !
//        std::cerr << "Probl�me d'ajout de Texture" << std::endl;
//        return 0;
//    }//*/
//}
//
//sf::RenderWindow & Moteur2D::getWindow()
//{
//    return *m_window;
//}
//
//const std::map <int, KeyboardListener*>& Moteur2D::getKeyboardListeners()
//{
//    return m_keyboardListeners;
//}
//const std::map <int, MouseListener*>& Moteur2D::getMouseListeners()
//{
//    return m_mouseListeners;
//}
//sf::Time Moteur2D::getTime()
//{
//    return m_clock.getElapsedTime();
//}





