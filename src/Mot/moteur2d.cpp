
#include "moteur2d.h"
#include <stdexcept>
#include <iostream>


#ifndef IN_QT

#else
#include <QTimer>
#endif

Moteur2D * Moteur2D::_instance = nullptr;

Moteur2D * Moteur2D::getInstance()
{
    if (_instance == nullptr)
    {

        _instance = new Moteur2D();
    }
    return _instance;
}

Moteur2D::Moteur2D() : _lastTime(0), _screenManager(nullptr), _keyboardListenersId(0), _mouseListenersId(0)
#ifndef IN_QT
        , _window(nullptr)
#else
        , _app(0), _eventsManager(0)
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
    if (_eventsManager) {
        delete _eventsManager;
    }

#endif
}


  /////////////////////////////////////////////////////
 ///////////          METHODES             ///////////
/////////////////////////////////////////////////////

void Moteur2D::init(int width, int height, std::string windowName, int, char **)
{
#ifdef IN_QT
    _app = new QApplication(argc, argv);

#else

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    _window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Close, settings);
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(false);

    // Prepare Font
    _font.loadFromFile("./motorResources/OpenSans-Regular.ttf");
#endif

    _screenSize.x = width;
    _screenSize.y = height;
    _eventsManager = new EventsManager();

#ifdef IN_QT
    _eventsManager->setFixedWidth(width);
    _eventsManager->setFixedHeight(height);
    _eventsManager->setWindowTitle(QString(windowName.c_str()));
    _app->installEventFilter(_eventsManager);

    _eventsManager->show();

    _timer.start();
#endif

}

void Moteur2D::run(ScreenManager* screenManager)
{
    _screenManager = screenManager;
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
    double s = 0;

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
    // double frameRate = 1000. / double(curTime - _lastTime);
    if (elapsedTime > 1./15.) {
        elapsedTime = 1./15.;
    }
    //std::cout << "RUN at " << frameRate << " frame per sec. elapsedTime = " << elapsedTime << " , curTime = " << curTime << std::endl;

    // Things to update here

#ifdef IN_QT
#else
    // Clear window
    _window->clear();
    // First called by eventmanager
    _eventsManager->eventLoop(*_window);
#endif


    if (_screenManager)
        _screenManager->baseUpdate(elapsedTime);

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


// ToDo reimplement
int Moteur2D::addKeyboardListener(KeyboardListener* kl)
{
    ++_keyboardListenersId;
    _keyboardListeners[_keyboardListenersId]=kl;
    return _keyboardListenersId;
}
int Moteur2D::addMouseListener(MouseListener* ml)
{
    ++_mouseListenersId;
    _mouseListeners[_mouseListenersId]=ml;
    return _mouseListenersId;
}

  /////////////////////////////////////////////////////
 ///////////          DELETERS             ///////////
/////////////////////////////////////////////////////

// ToDo reimplement
void Moteur2D::deleteKeyboardListener(int index)
{
    _keyboardListeners.erase(index);
}
void Moteur2D::deleteMouseListener(int index)
{
    _mouseListeners.erase(index);
}

void Moteur2D::unloadTexture(const std::string& imagePath)
{
    if (!imagePath.empty()) {
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



const std::map <int, KeyboardListener*>& Moteur2D::getKeyboardListeners()
{
    return _keyboardListeners;
}
const std::map <int, MouseListener*>& Moteur2D::getMouseListeners()
{
    return _mouseListeners;
}

Screen* Moteur2D::getCurrentScreen()
{
    return _screenManager->getCurrentScreen();
}

int Moteur2D::getCurrentScreenId()
{
    return _screenManager->getCurrentScreenId();
}






// Specific functions
#ifdef IN_QT
QWidget * Moteur2D::getView()
{
    return _eventsManager;
}
#else

sf::RenderWindow * Moteur2D::getWindow()
{
    return _window;
}
sf::Font & Moteur2D::getFont()
{
    return _font;
}
sf::Font & Moteur2D::setFont(std::string fontPath)
{
    _font.loadFromFile(fontPath);
    return _font;
}
#endif
