#include "GamePlay.h"
#include <cstdlib>
#include <ctime>

GamePlay::GamePlay()
    : _map()
{
    initPlayer();
   _health = new Health;
    initTile();
    initMap();
    createEnemies(0);
    _dt = 1.f;
}

GamePlay::~GamePlay()
{
    delete _player;
    delete _map;
    delete _tileText;
    cleanUpEnemies();
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

///Enemies
sf::Vector2f GamePlay::getRandomPos()
{
    float x = static_cast<float>(std::rand() % 1280);
    float y = static_cast<float>(std::rand() % 800);
    return sf::Vector2f(x, y);
}

void GamePlay::createEnemies(int c)
{
    for (int i = 0; i < c; ++i)
    {
        sf::Vector2f randomPos = getRandomPos();
        Enemy* newEnemy = new Enemy({randomPos});
        _enemies.push_back(newEnemy);
        ++_activeEnemiesCount;
    }
}

bool GamePlay::allEnemiesDead() const {
    for(const auto& enemy : _enemies) if(!enemy->isDead()) return false;
    return true;
}

void GamePlay::checkEnemyStatus()
{
    if(_activeEnemiesCount == 0) spawnNewEnemies();
}

void GamePlay::spawnNewEnemies()
{
    createEnemies(5);
}

void GamePlay::cleanUpEnemies()
{
    for(auto& enemy : _enemies)
    {
        delete enemy;
    }
    _enemies.clear();
}

sf::FloatRect GamePlay::getGlobalBoundsOfEnemies() const
{
    if(_enemies.empty()) return sf::FloatRect();
    sf::FloatRect enemyBounds = _enemies[0]->getGlobalBounds();
    for(size_t i = 1; i < _enemies.size(); ++i){
    sf::FloatRect currentEnemyBounds = _enemies[i]->getGlobalBounds();
    enemyBounds.left = std::min(enemyBounds.left, currentEnemyBounds.left);
    enemyBounds.top = std::min(enemyBounds.top, currentEnemyBounds.top);
    float right = std::max(enemyBounds.left + enemyBounds.width, currentEnemyBounds.left + currentEnemyBounds.width);
    float bottom = std::max(enemyBounds.top + enemyBounds.height, currentEnemyBounds.top + currentEnemyBounds.height);
    enemyBounds.width = right - enemyBounds.left;
    enemyBounds.height = bottom - enemyBounds.top;
    }
    return enemyBounds;
}

void GamePlay::updateEnemies(float dt)
{
    for(auto& enemy : _enemies) enemy->update(dt);
}

void GamePlay::chasePlayer(const sf::Vector2f& playerPos, float speed)
{
    for(auto& enemy : _enemies) enemy->chase(playerPos, speed);
}
///

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
    const int FILAS=17, COLS=40;
    int m[FILAS][COLS]
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,
        0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    _map = new Map(FILAS, COLS, _tileText, {32,32} );
    if(_map == nullptr)
    {
        std::cout<<"Error de asignacion de memoria a _map en Gameplay"<<std::endl;
        exit(-1);
    }
//
//    FILE *p = fopen("levelMap.dat", "rb");
//    if(p == nullptr)
//    {
//        std::cout<<"No se pudo abrir el archivo"<<std::endl;
//        exit(-1);
//    }
//    if(fread(&m, sizeof m,1, p ) ==  0 )
//    {   std::cout<<"Error no se pudo leer el archivo"<<std::endl;
//        exit(-1);
//    }
//    else std::cout<< "Se pudo leer el registro de mapa"<<std::endl;
//    fclose(p);
//

    for(int i=0; i<FILAS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            if(m[i][j] != 0){
                _map->addTile(i,j,_tileText,(m[i][j]-1));
            }

        }
    }

//    FILE *p = fopen("levelMap.dat", "ab");
//    if(p == nullptr)
//    {
//        std::cout<<"Error, no se pudo abrir el archivo"<<std::endl;
//        exit(-1);
//    }
//
//    if(fwrite(&m, sizeof m, 1, p)== 0) std::cout<<"no se pudo guardar el mapa"<<std::endl;
//    else std::cout<<"Mapa guardado" <<std::endl;
//    fclose(p);

}


void GamePlay::cmd()
{
    _player->cmd();

}

sf::Vector2f GamePlay::getPlayerPosition() const
{
    return _player->getHitBox().getPosition();
}

//sf::Vector2f GamePlay::getEnemyPosition() const
//{
//    return _enemies->getHitbox().getPosition();
//}



bool GamePlay::checkPlayerCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& obj)
{
    return playerBounds.intersects(obj);
}



const sf::Vector2f PLAYER_START_POSITION(100.0f, 540.0f);

void GamePlay::update()
{


    _player->update(_dt);
    sf::FloatRect playerBounds = _player->getHitBox();
    if(!_map->checkBottomBool(playerBounds))_player->setFall(_dt);
    sf::FloatRect playerNext = _player->getNextPos();
    sf::FloatRect enemyBounds = getGlobalBoundsOfEnemies();
    sf::FloatRect tileBounds;
    sf::Vector2f playerVel = _player->getVelocity();
    sf::Vector2f playerPos = _player->getPosition();
    chasePlayer(playerPos, 0.5f);

    bool isEnemyCollision = checkPlayerCollision( playerNext, enemyBounds);



    if(isEnemyCollision) _health->setHurt();

    if(playerVel.y >= 0 )
    {

        if(isEnemyCollision)
        {
            if( (playerBounds.top < enemyBounds.top) /// collision bottom player
                && (playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height))
            {
                // playerVel.y = 0.f;
                 _player->setQuiet();
                _player->setPosition( {((playerBounds.left) +13), ( enemyBounds.top) + 6} );
            }
        }
        else if(_map->checkIntersect(playerBounds) )
        {
            tileBounds = _map->checkTop(playerBounds);
            if( tileBounds != sf::FloatRect {0,0,0,0} )
            {
               // playerVel.y = 0.f;
                _player->setQuiet();
                _player->setPosition( {((playerBounds.left) +13), (tileBounds.top) +8} );
            }
        }
    }
    else if(playerVel.y < 0)
    {

        if(isEnemyCollision)
        {
            if( (playerBounds.top > enemyBounds.top) /// collision top player
                && (playerBounds.top + playerBounds.height > enemyBounds.top + enemyBounds.height))
            {
                _player->setPosition({ (playerBounds.left) + 13, ( enemyBounds.top + playerBounds.height) - 6});
            }
        }
    }

    if(playerVel.x > 0)
    {

        if(isEnemyCollision)
        {
            if( (playerBounds.left < enemyBounds.left) /// collision player right
                && (playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width) )
            {
                //playerVel.x = 0.f;
                _player->setPosition({ (enemyBounds.left - playerBounds.width), (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            }
        }
        else if(_map->checkIntersect(playerBounds) )
        {
            tileBounds = _map->checkRight(playerBounds);
            if( tileBounds != sf::FloatRect {0,0,0,0} )
            {
                 //playerVel.x = 0.f;

                _player->setPosition({ (tileBounds.left), (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            }
        }
    }
    else if(playerVel.x < 0)
    {

        if(isEnemyCollision)
        {
            if( (playerBounds.left > enemyBounds.left) /// collision player left
                && (playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width) )
            {
                //playerVel.x = 0.f;
                _player->setPosition({ (enemyBounds.left + playerBounds.width ), (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            }
        }
        else if(_map->checkIntersect(playerBounds) )
        {
            tileBounds = _map->checkLeft(playerBounds);
            if( tileBounds != sf::FloatRect {0,0,0,0} )
            {
                 //playerVel.x = 0.f;

                _player->setPosition({ (playerBounds.left+playerBounds.width)  , (_player->getGlobalBounds().top + _player->getGlobalBounds().height)});
            }
        }
    }

    _map->update(_dt);
    updateEnemies(_dt);
    _health->update();



}


void GamePlay::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*_map, states);
    target.draw(*_player, states);
    target.draw(*_health, states);
    for(const auto& enemy : _enemies) target.draw(*enemy, states);

}
