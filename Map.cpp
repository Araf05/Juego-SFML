#include "Map.h"

Map::Map()
{
    _texTile = nullptr;
    _tileSize = {};
}

Map::Map(int height, int width, sf::Texture* tile, sf::Vector2i tSize)
{
     _bak.setPosition({0,0});
     _texBak.loadFromFile("Background/night-town.png");
     _bak.setTexture(_texBak);
     _bak.scale(2.5f, 2.5f);

     _texTile = tile;
     _tileSize = tSize;
     _filas = height;
     _cols = width;

    _mTiles = new Tile**[_filas];
    if(_mTiles == nullptr)
    {
        std::cout<<"Error de aisgnacion de memoria, matriz de Tiles (cols)"<<std::endl;
        exit(-1);
    }
    for(int i=0; i<_filas; i++)
    {
        _mTiles[i] = new Tile*[_cols]{};
        if(_mTiles[i] == nullptr)
        {
            std::cout<<"Error de aisgnacion de memoria, matriz de Tiles (filas)"<<std::endl;
            exit(-1);
        }
    }

}



Map::~Map()
{
    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            delete _mTiles[i][j];
            _mTiles[i][j] = nullptr;
        }
    }
}


void Map::addTile(int x, int y, sf::Texture* vTex, int indexText)
{
    _texTile = vTex;
    if( (x<_filas) && (y<_cols) )
    {
        if(_mTiles[x][y] == nullptr)
        {
            _mTiles[x][y] = new Tile({(float)y*_tileSize.y,(float)(x+17)*_tileSize.x}, _texTile+indexText, sf::IntRect(0,0,_tileSize.x , _tileSize.y));
        }

    }

}
void Map::removeTile(int x, int y)
{
    if( (x<_cols) && (y<_filas) )
    {
        if(_mTiles[x][y] != nullptr)
        {
            delete _mTiles[x][y];
            _mTiles[x][y] = nullptr;
        }

    }
}

Tile Map::getTile(int posX, int posY)
{
    return **&_mTiles[posX][posY];
}


void Map::update(float dt)
{
    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            if(_mTiles[i][j]!= nullptr)
               _mTiles[i][j]->update(dt);
        }
    }
}



void Map::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            if(_mTiles[i][j]!= nullptr)
            {
                _mTiles[i][j]->draw(target, states);
            }
        }
    }
}
