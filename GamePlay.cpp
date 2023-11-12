#include "GamePlay.h"

GamePlay::GamePlay()
    : _map()
{
    initPlayer();
    _enemy = new Enemy({300, 540});
    initTile();
    initMap();
    _dt = 1.f;
}

GamePlay::~GamePlay()
{
    delete _player;
    delete _map;
    delete _enemy;
    delete _tileText;
}

void GamePlay::initPlayer()
{
    _player = new Personaje({100,540});
    if(_player == nullptr )
    {
        std::cout<<"Error de asignacion de memoria a _player en Gameplay"<<std::endl;
        exit(-1);
    }
}
void GamePlay::initTile()
{
    _tileText = new sf::Texture[5];
    if(_tileText == nullptr)
    {
        std::cout<<"Error de asignacion de memoria a _tileText en Gameplay"<<std::endl;
        exit(-1);
    }

    if(!_tileText[0].loadFromFile("Tileset/platforms11.png") )
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }
    if(!_tileText[1].loadFromFile("Tileset/grass11.png"))
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }
    if(!_tileText[2].loadFromFile("Tileset/bridge3.png") )
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }
    if(!_tileText[3].loadFromFile("Tileset/water1.png") )
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }
    if(!_tileText[4].loadFromFile("Tileset/tileMain23.png") )
    {
        std::cout<<"Error al cargar textura de tile en Gameplay"<<std::endl;
        exit(-1);
    }

}
void GamePlay::initMap()
{
    const int FILAS=17, COLS=241;
    int m[FILAS][COLS];

    _map = new Map(FILAS, COLS, _tileText, {16,16} );
    if(_map == nullptr)
    {
        std::cout<<"Error de asignacion de memoria a _map en Gameplay"<<std::endl;
        exit(-1);
    }

    FILE *p = fopen("levelMap.dat", "rb");
    if(p == nullptr)
    {
        std::cout<<"No se pudo abrir el archivo"<<std::endl;
        exit(-1);
    }
    if(fread(&m, sizeof m,1, p ) ==  0 )
    {   std::cout<<"Error no se pudo leer el archivo"<<std::endl;
        exit(-1);
    }
    else std::cout<< "Se pudo leer el registro de mapa"<<std::endl;
    fclose(p);


    for(int i=0; i<FILAS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            if(m[i][j] != 0){
                _map->addTile(i,j,_tileText,(m[i][j]-1));
            }

        }
    }

}


void GamePlay::cmd()
{
    _player->cmd();
    _enemy->cmd();

}

sf::Vector2f GamePlay::getPlayerPosition() const
{
    return _player->getHitBox().getPosition();
}

sf::Vector2f GamePlay::getEnemyPosition() const
{
    return _enemy->getHitBox().getPosition();
}



bool GamePlay::checkPlayerEnemyCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& enemyBounds)
{
    return playerBounds.intersects(enemyBounds);
}



const sf::Vector2f PLAYER_START_POSITION(100.0f, 540.0f);

void GamePlay::update()
{

    sf::FloatRect playerBounds = _player->getHitBox();
    sf::FloatRect playerNext = _player->getNextPos()
    ;
    sf::FloatRect enemyBounds = _enemy->getHitBox();
    sf::Vector2f playerVel = _player->getVelocity();

    if(checkPlayerEnemyCollision( playerNext, enemyBounds))
    {
        if(playerVel.y > 0) {
            if( (playerBounds.top < enemyBounds.top) /// collision bottom player
                && (playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height))
            {
                playerVel.y = 0.f;
                _player->setQuiet();
                _player->setPosition( {(playerBounds.left), ( enemyBounds.top - playerBounds.height)} );
            }
        }
        if(playerVel.y < 0 )
        {
            if( (playerBounds.top > enemyBounds.top) /// collision top player
                && (playerBounds.top + playerBounds.height > enemyBounds.top + enemyBounds.height))
            {
                playerVel.y = 0.f;
                _player->setPosition({ (playerBounds.left), ( enemyBounds.top + playerBounds.height)});
            }
        }

        if(playerVel.x > 0){
         if( (playerBounds.left < enemyBounds.left) /// collision player right
            && (playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width) )
        {
            playerVel.x = 0.f;
            _player->setPosition({ (enemyBounds.left - playerBounds.width), (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            //std::cout<<"derecha"<<std::endl;
        }
        }
        if(playerVel.x<0){

        if( (playerBounds.left > enemyBounds.left) /// collision player left
            && (playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width))
        {
            playerVel.x = 0.f;
            _player->setPosition({ (enemyBounds.left + enemyBounds.width),(_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            //std::cout<<"izquierda"<<std::endl;
        }
        }
        _player->setVelocity(playerVel);
    }

    if(_map->checkIntersect(playerBounds) )
    {
        sf::FloatRect tileBounds = _map->checkBottom(playerBounds);
        if( tileBounds != sf::FloatRect {0,0,0,0} )
        {
            std::cout<<"piso"<<std::endl;
           // playerVel.y = 0.f;
            _player->setQuiet();
            _player->setPosition( {(playerBounds.left), ( tileBounds.top)} );
            std::cout<<"piso"<<std::endl;

        }


//        if(playerVel.y < 0 )
//        {
//            if( (playerBounds.top > tileBounds.top) /// collision player bottom
//                && (playerBounds.top + playerBounds.height > tileBounds.top + tileBounds.height))
//            {
//               // playerVel.y = 0.f;
//                //_player->setPosition({ (playerBounds.left), ( tileBounds.top + playerBounds.height)});
//                std::cout<<""<<std::endl;
//            }
//        }

        if( (playerBounds.left < tileBounds.left) /// collision player right
            && (playerBounds.left + playerBounds.width < tileBounds.left + tileBounds.width) )
        {
//            playerVel.x = 0.f;
//            _player->setPosition({ (tileBounds.left - playerBounds.width), (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            //std::cout<<"derecha"<<std::endl;
        }


    }


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
