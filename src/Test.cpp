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

using namespace std;


int main(int argc, char **argv)
{

    Moteur2D* moteur = Moteur2D::getInstance();

    moteur->init(1024, 768, "Test", argc, argv);

    moteur->run(new GameManager());
    //std::cout << moteur->getTime().asSeconds() << std::endl;
    return 0;

}

