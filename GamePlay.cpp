#include "GamePlay.h"

GamePlay::GamePlay()
    : _map()
{
    initPlayer();
    _enemy = new Enemy({300, 550});
    initTile();
    initMap();
    _dt = 0.f;
}

GamePlay::~GamePlay()
{
    delete _player;
    delete _map;
    delete _enemy;
}

void GamePlay::initPlayer()
{
    _player = new Personaje({100,550});
    if(_player == nullptr )
    {
        std::cout<<"Error de asignacion de memoria a _player en Gameplay"<<std::endl;
        exit(-1);
    }
}
void GamePlay::initTile()
{
    _tileText = new sf::Texture[2];
    if(_tileText == nullptr)
    {
        std::cout<<"Error de asignacion de memoria a _tileText en Gameplay"<<std::endl;
        exit(-1);
    }

    if(!_tileText[0].loadFromFile("EXTRAS/Platform.png") )
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }
}
void GamePlay::initMap()
{
    _map = new Map(40, 25, _tileText, 32);
    if(_map == nullptr)
    {
        std::cout<<"Error de asignacion de memoria a _map en Gameplay"<<std::endl;
        exit(-1);
    }
    _map->addTile(0,4);
}


void GamePlay::cmd()
{
    _player->cmd();
    _enemy->cmd();

}

void GamePlay::update()
{
    _dt=0;
    _dt++;
    _map->update(_dt);
    _player->update(_dt);
    _enemy->update(_dt);

}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(*_map);
    window.draw(*_player);
    window.draw(*_enemy);
}
