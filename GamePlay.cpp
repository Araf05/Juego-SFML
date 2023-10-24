#include "GamePlay.h"

GamePlay::GamePlay()
    : _player({750,600})
{
    //ctor
}

GamePlay::~GamePlay()
{
    //dtor
}

void GamePlay::cmd()
{
    _player.cmd();
}

void GamePlay::update(float dt)
{
    _player.update(dt);

}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(_player);
}
