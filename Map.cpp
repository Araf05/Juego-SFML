#include "Map.h"

//Map::Map()
//{
//    _texTile = nullptr;
//    _tileSize = 0;
//}

Map::Map(unsigned width, unsigned height, sf::Texture* tile, unsigned tileSize)
{
     _bak.setPosition({0,0});
     _texBak.loadFromFile("Background/night-town.png");
     _bak.setTexture(_texBak);
     _bak.scale(2.5f, 2.5f);

     _texTile = tile;
     _tileSize = tileSize;

    _mTiles.resize(width);
    for(unsigned i=0; i<_mTiles.size(); i++)
    {
        _mTiles[i].resize(height, nullptr);
    }


}

Map::~Map()
{
    for(unsigned i=0; i<_mTiles.size(); i++)
    {
        for(unsigned j=0; j<_mTiles[i].size(); j++)
        {
           delete  _mTiles[i][j];
           _mTiles[i][j] = nullptr;
        }
    }
}


void Map::addTile(unsigned x, unsigned y)
{
    if(x<_mTiles.size())
    {
        if(y<_mTiles[x].size())
        {
            if(_mTiles[x][y] == nullptr)
            {
                _mTiles[x][y] = new Tile(_texTile, sf::IntRect(0,0,_tileSize, _tileSize));
            }
        }
    }

}
void Map::removeTile(unsigned x, unsigned y)
{
    if(x<_mTiles.size())
    {
        if(y<_mTiles[x].size())
        {
            if(_mTiles[x][y] != nullptr)
            {
                delete _mTiles[x][y];
                _mTiles[x][y] = nullptr;
            }
        }
    }
}

void Map::update(float dt)
{
    for(unsigned i=0; i<_mTiles.size(); i++)
    {
        for(unsigned j=0; j<_mTiles[i].size(); j++)
        {
            if(_mTiles[i][j]!= nullptr)
               _mTiles[i][j]->update(dt);
        }
    }
}


void Map::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    for(unsigned i=0; i<_mTiles.size(); i++)
    {
        for(unsigned j=0; j<_mTiles[i].size(); j++)
        {
            if(_mTiles[i][j]!= nullptr)
            {
                _mTiles[i][j]->draw(target, states);
            }
        }
    }
}



