
#include <iostream>

#include "moteur2d.h"
#include "ScreenManagerTest.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char **argv)
{
    srand (static_cast<unsigned int>(time(nullptr)));

    Moteur2D *moteur = Moteur2D::getInstance();

    //moteur->init(1200, 1000, "LD40", argc, argv);
    moteur->init(1024, 768, "TU", argc, argv);

    moteur->run(new ScreenManagerTest());
    return 0;

}
