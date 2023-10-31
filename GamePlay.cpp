#include "GamePlay.h"

GamePlay::GamePlay()
    : _map()
{
    _player = new Personaje({100,550});
    _enemy = new Enemy({300, 550});
    _dt = 0.f;
}

GamePlay::~GamePlay()
{
    delete _player;
}

void GamePlay::cmd()
{
    _map.cmd();
    _player->cmd();
    _enemy->cmd();

}

void GamePlay::update()
{
    _dt=0;
    _dt++;
    _map.update(_dt);
    _player->update(_dt);
    _enemy->update(_dt);

}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(_map);
    window.draw(*_player);
    window.draw(*_enemy);
}
