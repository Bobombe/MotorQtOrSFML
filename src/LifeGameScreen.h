
#ifndef SRC_LifeGameScreen_H_
#define SRC_LifeGameScreen_H_

#include "Mot/Screen.h"
#include "Mot/Sprite.h"
#include "Mot/MouseAndKeyListener.h"
#include <map>

class LifeGameScreen : public Screen, public MouseAndKeyListener
{
protected:
    std::map<int, std::map<int, Sprite*> > _cellGrid;
    std::map<int, std::map<int, Sprite*> > _cellGrid2;
    Vector2d _cellSize;
    double _timeSinceLastGeneration;
    bool _play;
    bool _step;
    bool _movingLeft;
    bool _movingRight;
    bool _movingUp;
    bool _movingDown;
    Vector2d _mousePos;
public:
    LifeGameScreen();
    virtual ~LifeGameScreen();

    void newCell(int column, int line);
    void killCell(int column, int line);


    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);
    virtual void buttonPressed(MouseButton::MouseButton button, Vector2d pos);
    virtual void mouseMoved(Vector2d pos);
    virtual void mouseWheelMoved(float wheelMoveInDegree);

protected:
    virtual int update(double seconds);
    virtual int draw();

    void updateCell(int column, int line);
    bool cellAlive(int column, int line);
    int countNeighbourAlive(int column, int line);
};

#endif /* SRC_LifeGameScreen_H_ */
