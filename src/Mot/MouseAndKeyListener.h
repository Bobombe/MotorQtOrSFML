
#include "KeyboardListener.h"
#include "MouseListener.h"

#ifndef SRC_MOT_MOUSEANDKEYLISTENER_H_
#define SRC_MOT_MOUSEANDKEYLISTENER_H_

class MouseAndKeyListener : public KeyboardListener, public MouseListener
{
public:
    MouseAndKeyListener();
    virtual ~MouseAndKeyListener();

    int getScreenId();
    void setScreenId(int screenId);
};

#endif
