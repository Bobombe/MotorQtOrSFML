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

std::map<int, std::map<int, Cell*> > LifeGameScreen::_cellGrid;
WorldElement * LifeGameScreen::_rootForCells(0);

int LifeGameScreen::_nbCells(0);

Cell::Cell(int column, int line) : sprite(0), ul(0), u(0), ur(0), l(0), r(0), dl(0), d(0), dr(0), column(column), line(line),
        alive1(false), alive2(false), stepsStayingDead(0)
{
        sprite = new Sprite("./Ressources/deadCell.png");
        sprite->setParent(LifeGameScreen::_rootForCells);
        sprite->setPosition(Vector2d(column*sprite->getSize().x, line*sprite->getSize().y));
}

Cell::~Cell()
{
    if (sprite) delete sprite;
}

void Cell::born(int currentState)
{
    if (sprite) {
        sprite->setTexturePath("./Ressources/cell.png");
    } else {
        sprite = new Sprite("./Ressources/cell.png");
        sprite->setParent(LifeGameScreen::_rootForCells);
        sprite->setPosition(Vector2d(column*sprite->getSize().x, line*sprite->getSize().y));
    }
    if (currentState == 0) {
        alive2 = true;
    } else {
        alive1 = true;
    }

    // Retrieve all neighbor
    if (!ul) {
        ul = LifeGameScreen::cellAt(column-1, line-1);
        ul->dr = this;
    }
    if (!u) {
        u = LifeGameScreen::cellAt(column, line-1);
        u->d = this;
    }
    if (!ur) {
        ur = LifeGameScreen::cellAt(column+1, line-1);
        ur->dl = this;
    }
    if (!l) {
        l = LifeGameScreen::cellAt(column-1, line);
        l->r = this;
    }
    if (!r) {
        r = LifeGameScreen::cellAt(column+1, line);
        r->l = this;
    }
    if (!dl) {
        dl = LifeGameScreen::cellAt(column-1, line+1);
        dl->ur = this;
    }
    if (!d) {
        d = LifeGameScreen::cellAt(column, line+1);
        d->u = this;
    }
    if (!dr) {
        dr = LifeGameScreen::cellAt(column+1, line+1);
        dr->ul = this;
    }

    LifeGameScreen::_nbCells ++;
}

void Cell::kill(int currentState)
{
    sprite->setTexturePath("./Ressources/deadCell.png");
    if (currentState == 0) {
        alive2 = false;
    } else {
        alive1 = false;
    }

    LifeGameScreen::_nbCells --;
}

bool Cell::updateCell(int currentState)
{
    bool needToBeDeleted = false;
    int count = 0;
    if (ul && ul->alive(currentState)) count++;
    if (u && u->alive(currentState)) count++;
    if (ur && ur->alive(currentState)) count++;
    if (l && l->alive(currentState)) count++;
    if (r && r->alive(currentState)) count++;
    if (dl && dl->alive(currentState)) count++;
    if (d && d->alive(currentState)) count++;
    if (dr && dr->alive(currentState)) count++;

    if (alive(currentState) && (count < 2 || count > 3)) {
        kill(currentState);
    } else if (!alive(currentState) && count == 3) {
        born(currentState);
        stepsStayingDead = 0;
    } else {
        if (currentState == 0) {
            alive2 = alive1;
        } else {
            alive1 = alive2;
        }
        if (!alive1 && !alive2 && count==0) {
            stepsStayingDead++;
            if (stepsStayingDead>2) {
                needToBeDeleted = true;
            }
        } else {
            stepsStayingDead = 0;
        }
    }
    return needToBeDeleted;
}

bool Cell::alive(int currentState)
{
    if (currentState == 0) {
        return alive1;
    }
    return alive2;
}
void Cell::safeDelete()
{

    int count = 0;
    if (ul && (ul->alive(0) || ul->alive(1))) count++;
    if (u && (u->alive(0) || u->alive(1))) count++;
    if (ur && (ur->alive(0) || ur->alive(1))) count++;
    if (l && (l->alive(0) || l->alive(1))) count++;
    if (r && (r->alive(0) || r->alive(1))) count++;
    if (dl && (dl->alive(0) || dl->alive(1))) count++;
    if (d && (d->alive(0) || d->alive(1))) count++;
    if (dr && (dr->alive(0) || dr->alive(1))) count++;
    if (count==0) {
        // Retrieve all neighbor
        if (ul) {
            ul->dr = 0;
        }
        if (u) {
            u->d = 0;
        }
        if (ur) {
            ur->dl = 0;
        }
        if (l) {
            l->r = 0;
        }
        if (r) {
            r->l = 0;
        }
        if (dl) {
            dl->ur = 0;
        }
        if (d) {
            d->u = 0;
        }
        if (dr) {
            dr->ul = 0;
        }
        std::map<int, std::map<int, Cell*> >::iterator itC = LifeGameScreen::_cellGrid.find(column);
        if (itC != LifeGameScreen::_cellGrid.end()) {
            std::map<int, Cell*> &cellLine = LifeGameScreen::_cellGrid[column];
            std::map<int, Cell*>::iterator itL = cellLine.find(line);
            if (itL != cellLine.end()) {
                cellLine.erase(itL);
                if (cellLine.empty()) {
                    LifeGameScreen::_cellGrid.erase(itC);
                }
            }
        }
        delete this;
    }
}









LifeGameScreen::LifeGameScreen() : Screen(), _timeSinceLastGeneration(0), _stepsSinceLastGeneration(0),
        _play(false), _step(false),
        _movingLeft(false), _movingRight(false), _movingUp(false), _movingDown(false),
        _fps("0 fps", this, 10), _nbGenerationsText("0th generation", this, 10),
        _nbGenerations(0), _gpsCible(60), _gpsText("0/60gps", this, 10), _nbCellsText("0 fps", this, 10), _state(0)
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

/*
    switchCell(0, 0);
    switchCell(1, 0);
    switchCell(2, 0);

    /*/

    switchCell(0, 0);
    switchCell(0, 1);
    switchCell(1, 0);
    switchCell(1, 1);

    switchCell(4, 0);
    switchCell(4, 1);
    switchCell(4, 2);
    switchCell(5, 0);
    switchCell(5, 1);
    switchCell(5, 2);

    switchCell(9, -2);
    switchCell(9, -1);
    switchCell(9, 3);
    switchCell(9, 4);
    switchCell(10, -1);
    switchCell(10, 0);
    switchCell(10, 1);
    switchCell(10, 2);
    switchCell(10, 3);
    switchCell(11, 0);
    switchCell(11, 1);
    switchCell(11, 2);
    switchCell(12, 1);

    switchCell(26, 1);
    switchCell(26, 2);
    switchCell(26, -3);
    switchCell(26, -4);
    switchCell(27, -2);
    switchCell(27, -1);
    switchCell(27, 0);
    switchCell(28, -3);
    switchCell(28, 1);
    switchCell(29, -2);
    switchCell(29, 0);
    switchCell(30, -1);

    switchCell(34, -1);
    switchCell(34, -2);
    switchCell(35, -1);
    switchCell(35, -2);
    //*/

    //_cellGrid = _cellGrid2;
    setScreenId(2);
}

LifeGameScreen::~LifeGameScreen()
{
}
Cell * LifeGameScreen::switchCell(int column, int line)
{
    Cell * cell = cellAt(column, line);
    int prevState = _state+1;
    if (prevState>1) prevState = 0;
    // update same state
    if (cell->alive(prevState)) {
        cell->kill(_state);
    } else {
        cell->born(_state);
    }
    return cell;
}
Cell * LifeGameScreen::cellAt(int column, int line)
{
    Cell * ret = 0;
    std::map<int, std::map<int, Cell*> >::iterator itC = _cellGrid.find(column);
    if (itC != _cellGrid.end()) {
        std::map<int, Cell*> cellLine = _cellGrid[column];
        std::map<int, Cell*>::iterator itL = cellLine.find(line);
        if (itL != cellLine.end()) {
            ret = itL->second;
        }
    }
    if (!ret) {
        ret = new Cell(column, line);
        _cellGrid[column][line] = ret;
    }
    return ret;
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
    _nbCellsText.setText(SSTR(LifeGameScreen::_nbCells << " cells."));

    if (_play) {
        _step = false;
        double stepByframe = ((double)(_gpsCible))*seconds;
        _stepsSinceLastGeneration+= stepByframe;
        _timeSinceLastGeneration += seconds;
        if (_stepsSinceLastGeneration >= 1) {
            int steps = _stepsSinceLastGeneration;
            double trueGps = ((double)(steps))/_timeSinceLastGeneration;
            for (int i = 0; i < steps; i++) {
                std::vector<Cell*> cellToDelete;
                _state++; if (_state>1) _state = 0;
                // Begin Algo
                for (std::map<int, std::map<int, Cell*> >::iterator itC=_cellGrid.begin(); itC!=_cellGrid.end(); ++itC) {
                    for (std::map<int, Cell*>::iterator itL=itC->second.begin(); itL!=itC->second.end(); ++itL) {
                        if (itL->second->updateCell(_state)) {
                            cellToDelete.push_back(itL->second);
                        }
                    }
                }
                for (int j = 0; j < cellToDelete.size(); j++) {
                    cellToDelete[j]->safeDelete();
                }
                //_cellGrid = _cellGrid2;
                // END Algo
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
        _state++; if (_state>1) _state = 0;
        std::vector<Cell*> cellToDelete;
        for (std::map<int, std::map<int, Cell*> >::iterator itC=_cellGrid.begin(); itC!=_cellGrid.end(); ++itC) {
            for (std::map<int, Cell*>::iterator itL=itC->second.begin(); itL!=itC->second.end(); ++itL) {
                if (itL->second->updateCell(_state)) {
                    cellToDelete.push_back(itL->second);
                }
            }
        }
        for (int j = 0; j < cellToDelete.size(); j++) {
            cellToDelete[j]->safeDelete();
        }
        _nbGenerations ++;
        _nbGenerationsText.setText(SSTR(_nbGenerations << "th generation."));
        //_cellGrid = _cellGrid2;
    }
    _fps.setText(SSTR(1./seconds << " fps"));
    return 0;//Screen::update(seconds);
}













/*





void LifeGameScreen::killCell(int column, int line)
{
    std::map<int, std::map<int, Cell*> >::iterator itC = _cellGrid.find(column);
    if (itC != _cellGrid.end()) {
        std::map<int, Cell*> &cellLine = _cellGrid[column];
        std::map<int, Cell*>::iterator itL = cellLine.find(line);
        if (itL != cellLine.end()) {
            delete cellLine[line];
            cellLine.erase(itL);
            if (cellLine.empty()) {
                _cellGrid.erase(itC);
            }
            _nbCells --;
            _nbCellsText.setText(SSTR(_nbCells << " cells."));
        }
    }
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
} //*/

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
        std::map<int, std::map<int, Cell*> >::iterator itC = _cellGrid.begin();
        for (; itC != _cellGrid.end(); ++itC) {
            std::map<int, Cell*>::iterator itL = itC->second.begin();
            for (; itL != itC->second.end(); ++itL) {
                delete itL->second;
            }
        }
        _cellGrid.clear();
        //_cellGrid2.clear();
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
    Cell * cell = cellAt(column, line);
    int prevState = _state+1;
    if (prevState>1) prevState = 0;
    // update same state
    if (cell->alive(prevState)) {
        cell->kill(_state);
    } else {
        cell->born(_state);
    }
    //_cellGrid = _cellGrid2;
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



int LifeGameScreen::draw()
{
    int retValue = 0;
    retValue = Screen::draw();
    return retValue;
}


