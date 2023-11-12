#include "GamePlay.h"
#include <iomanip>
#include <SFML/Graphics.hpp>




GamePlay::GamePlay()
    : _map()
{
    initPlayer();
    _enemy = new Enemy({300, 550});
    initTile();
    initMap();
    _dt = 0.f;


    //Fuente
    if(!_font.loadFromFile("FONTS/Roboto-Regular.ttf")){
        std::cerr << "Error al cargar la fuente." << std::endl;
        exit(-1);
    }
    _timerText.setFont(_font);
    _timerText.setCharacterSize(50);
    _timerText.setFillColor(sf::Color::White);
    _timerText.setPosition(10,550);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    _player->disparar();
}

}


sf::Vector2f GamePlay::getPlayerPosition() const
{
    return _player->getPosition();
}

sf::Vector2f GamePlay::getEnemyPosition() const
{
    return _enemy->getPosition();
}

bool GamePlay::checkPlayerEnemyCollision()
{
    sf::FloatRect playerBounds = _player->getGlobalBounds();
    sf::FloatRect enemyBounds = _enemy->getGlobalBounds();

    return playerBounds.intersects(enemyBounds);
}


const sf::Vector2f PLAYER_START_POSITION(100.0f, 550.0f);

void GamePlay::update()
{


    float deltaTime = _timer.restart().asSeconds();
    _dt += deltaTime;
    _map->update(_dt);


    sf::Vector2f playerPos = getPlayerPosition();
    sf::Vector2f enemyPos = getEnemyPosition();

    _player->setEnemyPosition(enemyPos);
    _enemy->setPlayerPosition(playerPos);

    _renderDt = deltaTime;


    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << _dt;
    _timerText.setString(ss.str());


   //if(checkPlayerEnemyCollision())
    //{
     //   _player->setPosition(PLAYER_START_POSITION);
    //}




}

void GamePlay::draw( sf::RenderWindow& window)
{
    window.draw(*_map);
    window.draw(*_player);
    window.draw(*_enemy);
    window.draw(_timerText);

    _player->update(_renderDt);
    _enemy->update(_renderDt);
}
