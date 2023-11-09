#include "GamePlay.h"

GamePlay::GamePlay()
    : _map()
{
    initPlayer();
    _enemy = new Enemy({300, 568});
    initTile();
    initMap();
    _dt = 1.f;
}

GamePlay::~GamePlay()
{
    delete _player;
    delete _map;
    delete _enemy;
}

void GamePlay::initPlayer()
{
    _player = new Personaje({100,568});
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

void GamePlay::update()
{
//    _dt=0;
//    _dt++;
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
