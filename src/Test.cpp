//============================================================================
// Name        : Test.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Mot/moteur2d.h"
#include "GameManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char **argv)
{
    srand (time(NULL));

    Moteur2D* moteur = Moteur2D::getInstance();

    moteur->init(1200, 1000, "LD40", argc, argv);

    moteur->run(new GameManager());
    return 0;

}

