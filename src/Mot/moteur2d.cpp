
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

Moteur2D::Moteur2D() :
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
#ifndef IN_QT
    sf::ContextSettings settings;
    m_screenSize.x = width;
    m_screenSize.y = height;
    settings.antialiasingLevel = 4;
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Default, settings);

        // Init des Id
    m_keyboardListenersId = 0;
    m_mouseListenersId = 0;

    m_scm = 0;

    /* TODO sup pour ecran
    m_preDrawablesIndex = 0;
    m_drawablesIndex = 0;
    m_postDrawablesIndex = 0;
    //*/
#else
    _app = new QApplication(argc, argv);
    _view = new QGraphicsView();
    _view->setFixedWidth(width);
    _view->setFixedHeight(height);
    _view->show();

#endif
}

void Moteur2D::run()
{

#ifndef IN_QT
    EventManager em;
    m_t = m_clock.getElapsedTime();
    sf::Time t2;
    float s;
    m_window->setVerticalSyncEnabled(true);
    //m_window->setFramerateLimit(60);

    while(m_window->isOpen())
    {
        // On efface la fen�tre d�s le d�but pour permettre aux Updatables de d�ssiner
        m_window->clear();// efface la fen�tre

        // TO DO : Relacher le proc
        //Attente
        // Attente active
        do
        {
            t2 = m_clock.getElapsedTime();
            s = (t2-m_t).asSeconds() ;
        }while (s<1/60.);

        // First called by eventmanager
        em.eventLoop(*m_window);

        //Mise � jour des �l�ments
        for (std::map<int,Updatable*>::iterator it=m_updates.begin(); it!=m_updates.end(); ++it)
        {
            (it->second)->update(s);
        }
        if (m_scm)
            m_scm->update(s);

        /*/ Dessine tous les objets dessinables => TODO dans les Ecrans
        for (std::map<int,sf::Sprite*>::iterator it=m_preDraw.begin(); it!=m_preDraw.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        for (std::map<int,sf::Sprite*>::iterator it=m_drawables.begin(); it!=m_drawables.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        for (std::map<int,sf::Sprite*>::iterator it=m_postDraw.begin(); it!=m_postDraw.end(); ++it)
        {
            m_window->draw(*(it->second));
        }*/
        if (m_scm)
            m_scm->draw();

        m_window->display();// Affiche

        //MaJ temps
        m_t = t2;

    }
#else
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60);
    _app->exec();


#endif
}

void Moteur2D::update()
{
    std::cout << "RUN" << std::endl;
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





