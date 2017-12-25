
#ifndef SRC_LifeGameScreen_H_
#define SRC_LifeGameScreen_H_

#include "Mot/Screen.h"
#include "Mot/Sprite.h"
#include "Mot/WorldElement.h"
#include "Mot/Text.h"
#include "Mot/MouseAndKeyListener.h"
#include <map>

class Cell
{
public :
    Sprite* sprite;
    Cell * ul;
    Cell * u;
    Cell * ur;
    Cell * l;
    Cell * r;
    Cell * dl;
    Cell * d;
    Cell * dr;

    int column;
    int line;
    bool alive1;
    bool alive2;

    int stepsStayingDead;

    Cell(int column, int row);
    virtual ~Cell();

    void born(int currentState = 0);
    void kill(int currentState = 0);
    bool updateCell(int currentState);

    bool alive(int state);

    void safeDelete();

};

class LifeGameScreen : public Screen, public MouseAndKeyListener
{
public:

    static std::map<int, std::map<int, Cell*> > _cellGrid;
    //static std::map<int, std::map<int, Cell*> > _cellGrid2;

    static WorldElement * _rootForCells;

    static int _nbCells;

protected:
    Vector2d _cellSize;
    double _timeSinceLastGeneration;
    double _stepsSinceLastGeneration;
    bool _play;
    bool _step;
    bool _movingLeft;
    bool _movingRight;
    bool _movingUp;
    bool _movingDown;
    Vector2d _mousePos;

    Text _fps;
    Text _nbGenerationsText;
    int _nbGenerations;

    int _gpsCible;
    Text _gpsText;
    Text _nbCellsText;

    int _state;



public:
    LifeGameScreen();
    virtual ~LifeGameScreen();

    Cell * switchCell(int column, int line);
    static Cell * cellAt(int column, int line);

protected:
    virtual int update(double seconds);

public:






    //void killCell(int column, int line);

    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);
    virtual void buttonPressed(MouseButton::MouseButton button, Vector2d pos);
    virtual void mouseMoved(Vector2d pos);
    virtual void mouseWheelMoved(float wheelMoveInDegree);

protected:
    virtual int draw();

//    void updateCell(int column, int line);
//    bool cellAlive(int column, int line);
//    int countNeighbourAlive(int column, int line);
};

#endif /* SRC_LifeGameScreen_H_ */
