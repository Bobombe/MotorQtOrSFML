/* decomment to test
#include <iostream>

#include "moteur2d.h"
#include "ScreenManagerTest.h"
#include "LD45/ScreenManagerLD45.h"
#include "LD46/LD46ScreenManager.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand (static_cast<unsigned int>(time(nullptr)));

    Moteur2D *moteur = Moteur2D::getInstance();

    moteur->init(1024, 768, "LD45", argc, argv);

    moteur->run(new ScreenManagerTest());
    //moteur->run(new LD46ScreenManager());
    //moteur->run(new ScreenManagerLD45());
    return 0;

}//*/
