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
    createEnemies(2);
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

std::vector<sf::FloatRect> GamePlay::getGlobalBoundsOfEnemies() const
{
    std::vector<sf::FloatRect> allEnemyBounds;
    if(_enemies.empty()) return std::vector<sf::FloatRect> {};

    for(int i = 0; i < _enemies.size(); i++)
    {
        sf::FloatRect enemyBounds = _enemies[i]->getHitBox();
        allEnemyBounds.push_back(enemyBounds);
    }

    return allEnemyBounds;
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
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,
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


bool GamePlay::checkPlayerCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& obj)
{
    return playerBounds.intersects(obj);
}


void GamePlay::mapCollisionHandler(sf::Vector2f p, sf::FloatRect t, sf::FloatRect pb)
{
    ///PB -> PLAYERBOUNDS
    ///T -> TILEBOUNDS
    ///P -> PLAYER VECTOR2F

    if(p.y >= 0){
        if(_map->checkIntersect(pb)){
            t = _map->checkTop(pb);
            if(t != sf::FloatRect{0,0,0,0}){
                _player->setQuiet();
                _player->setPosition({pb.left + 13, t.top + 6});
            }
        }
    }
}

sf::FloatRect GamePlay::enemyCollisionHandler(sf::FloatRect pn, sf::FloatRect eb)
{
    ///PN -> PLAYERNEXT
    ///EB -> ENEMYBOUNDS

 std::vector<sf::FloatRect> allEnemyBounds = getGlobalBoundsOfEnemies();

    if(allEnemyBounds.empty()) return eb;

 bool isEnemyCollision = false;
 int i = 0;
 while(!isEnemyCollision && i < allEnemyBounds.size())
 {
     isEnemyCollision = checkPlayerCollision (pn , allEnemyBounds[i]);
     eb = allEnemyBounds[i];
     i++;
 }


    return eb;
}



void GamePlay::update()
{

    _player->update(_dt);
    sf::FloatRect playerBounds = _player->getHitBox();
    if(!_map->checkBottomBool(playerBounds))_player->setFall(_dt);
    sf::FloatRect playerNext = _player->getNextPos();
    sf::FloatRect tileBounds;
    sf::Vector2f playerVel = _player->getVelocity();
    sf::Vector2f playerPos = _player->getPosition();

    chasePlayer(playerPos, 0.5f);
    sf::FloatRect enemyBounds = enemyCollisionHandler(playerNext, enemyBounds);
    mapCollisionHandler(playerVel, tileBounds, playerBounds);


    if(checkPlayerCollision(playerBounds, enemyBounds)) std::cout << "choco" << std::endl;

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
