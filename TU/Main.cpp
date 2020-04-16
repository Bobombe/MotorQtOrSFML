
#include <iostream>

#include "moteur2d.h"
#include "ScreenManagerTest.h"
#include "LD45/ScreenManagerLD45.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char **argv)
{
    std::cout << "Youpi : " << std::endl;
    srand (static_cast<unsigned int>(time(nullptr)));

    std::cout << "Youpi : " << std::endl;
    Moteur2D *moteur = Moteur2D::getInstance();

    std::cout << "Youpi : " << std::endl;
    moteur->init(1024, 768, "LD45", argc, argv);

    std::cout << "Youpi : " << std::endl;
    //moteur->run(new ScreenManagerTest());
    moteur->run(new ScreenManagerLD45());
    std::cout << "Youpi : " << std::endl;
    return 0;

}
