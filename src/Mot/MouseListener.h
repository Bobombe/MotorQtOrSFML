
#ifndef SRC_MOT_MOUSELISTENER_H_
#define SRC_MOT_MOUSELISTENER_H_

#include "Vector2d.h"

namespace MouseButton
{
    enum MouseButton {
        Unknown = -1,
	    left = 0,
		middle,
		right
    };
}

class MouseListener {

protected:
    int _id;
    int _screenIdMouse; // used to pass keyboard inputs only to the current screen

public:
	MouseListener();
	virtual ~MouseListener();

    virtual void buttonPressed(MouseButton::MouseButton button, Vector2d pos){};
    virtual void buttonReleased(MouseButton::MouseButton button, Vector2d pos){};
    virtual void mouseMoved(Vector2d pos){};
    virtual void mouseWheelMoved(float wheelMoveInDegree){};

    int getScreenIdMouse();
    void setScreenIdMouse(int screenId);
};

#endif
