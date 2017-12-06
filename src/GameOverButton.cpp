#include "GameOverButton.h"

GameOverButton::GameOverButton() : Button("./resLD40/buttonGameOver.png", Vector2d(0, 0), Vector2d(200,100))
{
    _weName = "GameOverButton";
    setPosition(Vector2d(300, 400));
    _gameOverText = new Text("Game Over", this);
    _gameOverText->setCharacterSize(50);
    _gameOverText->setColor(Text::Black);
    //ctor
}

GameOverButton::~GameOverButton()
{
    //dtor
}
