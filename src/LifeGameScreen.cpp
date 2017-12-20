/*
 * StartScreenLD40.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: dev
 */

#include "LifeGameScreen.h"
#include "Mot/moteur2d.h"
#include "Mot/Sprite.h"
#include <iostream>
#include <sstream>
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
LifeGameScreen::LifeGameScreen() : Screen(), _timeSinceLastGeneration(0), _stepsSinceLastGeneration(0),
        _play(false), _step(false),
        _movingLeft(false), _movingRight(false), _movingUp(false), _movingDown(false),
        _fps("0 fps", this, 10), _nbCellsText("0 fps", this, 10), _nbCells(0),
        _nbGenerationsText("0th generation", this, 10), _nbGenerations(0), _gpsCible(60), _gpsText("0/60gps", this, 10)
{
    _fps.setPosition(Vector2d(5, 5));
    _nbCellsText.setPosition(Vector2d(5, 25));
    _nbGenerationsText.setPosition(Vector2d(5, 45));
    _gpsText.setPosition(Vector2d(5, 65));
    _fps.setCharacterSize(12);
    _nbCellsText.setCharacterSize(12);
    _nbGenerationsText.setCharacterSize(12);
    _gpsText.setCharacterSize(12);
    _rootForCells = new WorldElement(this);
    _rootForCells->setPosition(Vector2d(Moteur2D::getInstance()->getScreenSize().x/2, Moteur2D::getInstance()->getScreenSize().y/2));
    _rootForCells->setScale(0.5);

    Sprite * cell = new Sprite("./Ressources/cell.png");
    _cellSize = cell->getSize();
    delete cell;


//    newCell(0, 0);
//    newCell(1, 0);
//    newCell(2, 0);
//    newCell(2, 1);
//    newCell(1, 2);
//    newCell(-10, 0);
//    newCell(-9, 0);
//    newCell(-8, 0);
//    newCell(-8, 1);
//    newCell(-9, 2);

    newCell(0, 0);
    newCell(0, 1);
    newCell(1, 0);
    newCell(1, 1);

    newCell(4, 0);
    newCell(4, 1);
    newCell(4, 2);
    newCell(5, 0);
    newCell(5, 1);
    newCell(5, 2);

    newCell(9, -2);
    newCell(9, -1);
    newCell(9, 3);
    newCell(9, 4);
    newCell(10, -1);
    newCell(10, 0);
    newCell(10, 1);
    newCell(10, 2);
    newCell(10, 3);
    newCell(11, 0);
    newCell(11, 1);
    newCell(11, 2);
    newCell(12, 1);

    newCell(26, 1);
    newCell(26, 2);
    newCell(26, -3);
    newCell(26, -4);
    newCell(27, -2);
    newCell(27, -1);
    newCell(27, 0);
    newCell(28, -3);
    newCell(28, 1);
    newCell(29, -2);
    newCell(29, 0);
    newCell(30, -1);

    newCell(34, -1);
    newCell(34, -2);
    newCell(35, -1);
    newCell(35, -2);

    _cellGrid = _cellGrid2;
    setScreenId(2);
}

LifeGameScreen::~LifeGameScreen()
{
}


int LifeGameScreen::update(double seconds)
{
    double speed = 500*seconds;
    if (_movingLeft) {
        _rootForCells->movePosition(Vector2d(speed, 0));
    } else if (_movingRight) {
        _rootForCells->movePosition(Vector2d(-speed, 0));
    }
    if (_movingUp) {
        _rootForCells->movePosition(Vector2d(0, speed));
    } else if (_movingDown) {
        _rootForCells->movePosition(Vector2d(0, -speed));
    }
    if (_play) {
        _step = false;
        double stepByframe = ((double)(_gpsCible))*seconds;
        _stepsSinceLastGeneration+= stepByframe;
        _timeSinceLastGeneration += seconds;
        if (_stepsSinceLastGeneration >= 1) {
            int steps = _stepsSinceLastGeneration;
            double trueGps = ((double)(steps))/_timeSinceLastGeneration;
            for (int i = 0; i < steps; i++) {
                for (std::map<int, std::map<int, Sprite*> >::iterator itC=_cellGrid.begin(); itC!=_cellGrid.end(); ++itC) {
                    for (std::map<int, Sprite*>::iterator itL=itC->second.begin(); itL!=itC->second.end(); ++itL) {
                        for (int i = -1; i < 2; i++) {
                            for (int j = -1; j < 2; j++) {
                                updateCell(itC->first + i, itL->first + j);
                            }
                        }
                    }
                }
                _cellGrid = _cellGrid2;
            }
            _stepsSinceLastGeneration -= steps;
            _timeSinceLastGeneration = 0;
            // Update texts
            _nbGenerations += stepByframe;
            _nbGenerationsText.setText(SSTR(_nbGenerations << "th generation."));
            _gpsText.setText(SSTR(trueGps << "/" << _gpsCible <<"gps"));
        }
    } else if (_step) {
        _step = false;
        for (std::map<int, std::map<int, Sprite*> >::iterator itC=_cellGrid.begin(); itC!=_cellGrid.end(); ++itC) {
            for (std::map<int, Sprite*>::iterator itL=itC->second.begin(); itL!=itC->second.end(); ++itL) {
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        updateCell(itC->first + i, itL->first + j);
                    }
                }
            }
        }
        _cellGrid = _cellGrid2;
    }
    _fps.setText(SSTR(1./seconds << " fps"));
    return 0;//Screen::update(seconds);
}

void LifeGameScreen::keyPressed(Key::Key key)
{
    if (key == Key::Left) {
        _movingLeft = true;
    } else if (key == Key::Right) {
        _movingRight = true;
    } else if (key == Key::Up) {
        _movingUp = true;
    } else if (key == Key::Down) {
        _movingDown = true;
    }
}
void LifeGameScreen::keyReleased(Key::Key key)
{
    if (key == Key::Space) {
        _play = !_play;
    } else if (key == Key::Left) {
        _movingLeft = false;
    } else if (key == Key::Right) {
        _movingRight = false;
    } else if (key == Key::Up) {
        _movingUp = false;
    } else if (key == Key::Down) {
        _movingDown = false;
    } else if (key == Key::R) {
        std::map<int, std::map<int, Sprite*> >::iterator itC = _cellGrid2.begin();
        for (; itC != _cellGrid2.end(); ++itC) {
            std::map<int, Sprite*>::iterator itL = itC->second.begin();
            for (; itL != itC->second.end(); ++itL) {
                delete itL->second;
            }
        }
        _cellGrid.clear();
        _cellGrid2.clear();
        _nbCells = 0;
        _nbCellsText.setText(SSTR(_nbCells << " cells."));
        _nbGenerations = 0;
        _nbGenerationsText.setText(SSTR(_nbGenerations << "th generation."));
    } else if (key == Key::P) {
        _gpsCible *= 2;
    } else if (key == Key::M) {
        _gpsCible /= 2;
    } else if (key == Key::S) {
        _step = true;
    } else if (key == Key::C) {
        _rootForCells->setScale(0.5);
        _rootForCells->setPosition(Vector2d(Moteur2D::getInstance()->getScreenSize().x/2, Moteur2D::getInstance()->getScreenSize().y/2));
    }
}
void LifeGameScreen::buttonPressed(MouseButton::MouseButton button, Vector2d pos)
{
    pos = (pos - _rootForCells->getPosition())/_rootForCells->getScale();
    double column = pos.x/_cellSize.x;
    if (column < 0) {
        column--;
    }
    double line = pos.y/_cellSize.y;
    if (line < 0) {
        line--;
    }
    if (cellAlive(column, line)) {
        killCell(column, line);
    } else {
        newCell(column, line);
    }
    _cellGrid = _cellGrid2;
}
void LifeGameScreen::mouseMoved(Vector2d pos)
{
    _mousePos = pos;
}
void LifeGameScreen::mouseWheelMoved(float wheelMoveInDegree)
{
    Vector2d screenPos = _rootForCells->getPosition();
    double screenScale = _rootForCells->getScale();
    double newScreenScale = screenScale;
    Vector2d mouseRelativPos = (_mousePos-screenPos)/screenScale;

    if (wheelMoveInDegree > 0) {
        newScreenScale = screenScale*2.;
        _rootForCells->setScale(newScreenScale);
    } else {
        newScreenScale = screenScale/2.;
        _rootForCells->setScale(newScreenScale);
    }

    Vector2d newScreenPos = mouseRelativPos*screenScale + screenPos - mouseRelativPos*newScreenScale;
    _rootForCells->setPosition(newScreenPos);
}




void LifeGameScreen::newCell(int column, int line)
{
    bool addIt = true;
    std::map<int, std::map<int, Sprite*> >::iterator itC = _cellGrid2.find(column);
    if (itC != _cellGrid2.end()) {
        std::map<int, Sprite*> cellLine = _cellGrid2[column];
        std::map<int, Sprite*>::iterator itL = cellLine.find(line);
        if (itL != cellLine.end()) {
            addIt = false;
        }
    }
    if (addIt) {
        Sprite * cell = new Sprite("./Ressources/cell.png");
        cell->setParent(_rootForCells);
        cell->setPosition(Vector2d(column*cell->getSize().x, line*cell->getSize().y));
        _cellGrid2[column][line] = cell;
        _nbCells ++;
        _nbCellsText.setText(SSTR(_nbCells << " cells."));
    }
}
void LifeGameScreen::killCell(int column, int line)
{
    std::map<int, std::map<int, Sprite*> >::iterator itC = _cellGrid2.find(column);
    if (itC != _cellGrid2.end()) {
        std::map<int, Sprite*> &cellLine = _cellGrid2[column];
        std::map<int, Sprite*>::iterator itL = cellLine.find(line);
        if (itL != cellLine.end()) {
            delete cellLine[line];
            cellLine.erase(itL);
            if (cellLine.empty()) {
                _cellGrid2.erase(itC);
            }
            _nbCells --;
            _nbCellsText.setText(SSTR(_nbCells << " cells."));
        }
    }
}
int LifeGameScreen::draw()
{
    int retValue = 0;
    retValue = Screen::draw();
    return retValue;
}

void LifeGameScreen::updateCell(int column, int line)
{
    int count = countNeighbourAlive(column, line);
    if (cellAlive(column, line)) {
        if (count < 2 || count > 3) {
            killCell(column, line);
        }
    } else {
        if (count == 3) {
            newCell(column, line);
        }
    }
}

bool LifeGameScreen::cellAlive(int column, int line)
{
    bool alive = false;
    std::map<int, std::map<int, Sprite*> >::iterator itC = _cellGrid.find(column);
    if (itC != _cellGrid.end()) {
        if (itC->second.find(line) != itC->second.end()) {
            alive = true;
        }
    }
    return alive;
}
int LifeGameScreen::countNeighbourAlive(int column, int line)
{
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i || j) && cellAlive(column + i, line + j)) {
                count++;
            }
        }
    }
    return count;
}
