#include "GamePlay.h"

GamePlay::GamePlay()
    : _player({750,600})
{
    _dt = 0.f;
}

GamePlay::~GamePlay()
{
    //dtor
}

void GamePlay::cmd()
{
    _player.cmd();
}

void GamePlay::update()
{
    _dt++;
    _player.update(_dt);

}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(_player);
}
