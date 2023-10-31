#include "GamePlay.h"

GamePlay::GamePlay()
    : _player({750,600}), _enemy({0,0})
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
    _enemy.cmd();
}

void GamePlay::update()
{
    _dt=0;
    _dt++;
    _player.update(_dt);
    _enemy.update(_dt);

}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(_player);
    window.draw(_enemy);
}
