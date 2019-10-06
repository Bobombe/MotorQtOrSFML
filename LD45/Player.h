#ifndef Player_H
#define Player_H

#include "BaseCharacter.h"
#include "KeyboardListener.h"

class Player : public BaseCharacter, public KeyboardListener
{
public:
    Player();

    void keyPressed(Key::Key) override;
    void keyReleased(Key::Key) override;
};

#endif // Player_H
