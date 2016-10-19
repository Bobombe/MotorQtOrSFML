
#include "moteur2d.h"
#include <stdexcept>
#include <iostream>


    // Todo : things to suppress from test
#include <QGraphicsPixmapItem>

#ifndef IN_QT

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
    if (_scene) {
        delete _scene;
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
    _view->setWindowTitle(QString(windowName.c_str()));

    _view->show();

    _timer.start();

#else

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    _window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Default, settings);
    _window->setVerticalSyncEnabled(true);
#endif

    _screenWidth = width;
    _screenHeight = height;

}

void Moteur2D::run()
{


    // Todo : things to suppress from test
    _screenTest = new Screen();
    Sprite * sp = new Sprite("./Ressources/Fond3.png"/*, Vector2d(250, 150), Vector2d(20, 30)*/);
    //Sprite * sp2 = new Sprite("./Ressources/Fond3.png", Vector2d(150, 150), Vector2d(30, 20));
    sp->setSpeed(Vector2d(0, 00));
    sp->setPosition(Vector2d(0, _screenHeight-_screenHeight));
    //sp2->setSpeed(Vector2d(-50, 50));
    //sp2->setPosition(Vector2d(600, 0));
    _screenTest->addWorldElement(sp);
    _screenTest->setPosition(Vector2d(0, -_screenHeight));
    _screenTest->setSpeed(Vector2d(0, 100));
    //_screenTest->addWorldElement(sp2);


    _lastTime = getMsSinceLaunch();
    update();
#ifdef IN_QT
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60);
    _app->exec();

#else

    sf::Time t1 = _clock.getElapsedTime();
    sf::Time t2;
    float s = 0;

    while(_window->isOpen())
    {
        // TO DO : Relacher le proc
        // Attente active
        while (s<1/60.)
        {
            t2 = _clock.getElapsedTime();
            s = (t2-t1).asSeconds() ;
        }
        s=0;

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
    _window->clear();
#endif

    _screenTest->update(elapsedTime);
    _screenTest->draw();
    /*/ First called by eventmanager
    em.eventLoop(*m_window);

    if (m_scm)
        m_scm->update(s);

    if (m_scm)
        m_scm->draw();//*/

#ifdef IN_QT
#else
    // Display window
    _window->display();
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
void Moteur2D::unloadTexture(const std::string& imagePath)
{
    try
    {
        Texture* texture = _textures.at(imagePath);
        if (texture->freeTexture()) {
            _textures.erase(imagePath);
            delete texture;
        }
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << "ERROR : Moteur2D::unloadTexture : texture " << imagePath << " not stored." << std::endl;
    }

}

  /////////////////////////////////////////////////////
 ///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
// Permet l'acc�s aux textures, si la texture est inexistante cette methode la cr�era.

Texture * Moteur2D::getTexture(const std::string& imagePath)
{
    Texture* texture = 0;
    CoreTexture * coreTexture = 0;
    try
    {
        texture = _textures.at(imagePath);
        coreTexture = texture->getTexture();
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << "Moteur2D::getTexture : creating new texture from " << imagePath << "." << std::endl;
        texture = new Texture(imagePath);
        coreTexture = texture->getTexture();
        if (coreTexture) {
            _textures.insert(std::pair<std::string, Texture*>(imagePath, texture));
        } else {
            delete texture;
            std::cout << "ERROR : Moteur2D::getTexture : couldn't create new texture from " << imagePath << "." << std::endl;
        }
    }
    return texture;
}



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






// Specific functions
#ifdef IN_QT
QGraphicsView * Moteur2D::getView()
{
    return _view;
}
#else

#endif
