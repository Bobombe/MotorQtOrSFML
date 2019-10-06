#include "Player.h"

Player::Player()
{
}
void Player::keyPressed(Key::Key key)
{
    if (key == Key::Down) {
        setDown(true);
    } else if (key == Key::Left) {
        setLeft(true);
    } else if (key == Key::Right) {
        setRight(true);
    } else if (key == Key::Up) {
        setUp(true);
    } else if (key == Key::C) {
        getCollider()->setCollisionEnabled(!getCollider()->getCollisionEnabled());
    }
}
void Player::keyReleased(Key::Key key)
{
    if (key == Key::Down) {
        setDown(false);
    } else if (key == Key::Left) {
        setLeft(false);
    } else if (key == Key::Right) {
        setRight(false);
    } else if (key == Key::Up) {
        setUp(false);
    }
}
