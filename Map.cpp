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


void Map::addTile(int y, int x, sf::Texture* vTex, int indexText)
{
    _texTile = vTex + indexText;
    sf::Vector2f pos;
    int solid = 1;
    if(indexText == 1 || indexText == 3)
    {
        solid = 0;
    }

    if( (y<_filas) && (x<_cols) )
    {
        if(_mTiles[y][x] == nullptr)
        {
            pos.x = x*_tileSize.x;
            pos.y = (y+17)*_tileSize.y;
            _mTiles[y][x] = new Tile( pos, _texTile, (sf::IntRect(0,0,_tileSize.x , _tileSize.y)), solid );
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


bool Map::checkIntersect(const sf::FloatRect &player )
{
    bool collision = false;
    for(int i=0; i<80 ; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(( _mTiles[j][i] != nullptr) &&( _mTiles[j][i]->isSolid()) )
            {
                if(_mTiles[j][i]->getHitBox().intersects(player))
                {
                    collision = true;
                }
            }

        }
    }
    return collision;
}

const sf::FloatRect Map::checkTop(const sf::FloatRect &player) const
{
    int posx;
    posx = floor(player.left /16);
    sf::FloatRect tile = {};

    for(int i=posx; i<posx+1 ; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(( _mTiles[j][i] != nullptr) &&( _mTiles[j][i]->isSolid()) )
            {
                if(_mTiles[j][i]->getHitBox().top > player.top
                    && _mTiles[j][i]->getGlobalBounds().top + _tileSize.y > player.top + player.height )
                {
                    return tile = _mTiles[j][i]->getHitBox();
                }
            }
        }
    }
    return tile;
}

const sf::FloatRect Map::checkBottom(const sf::FloatRect &player) const
{
    int posx;
    posx = floor(player.left /16);
    sf::FloatRect tile = {};

    for(int i=posx; i<posx+1 ; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(( _mTiles[j][i] != nullptr) &&( _mTiles[j][i]->isSolid()) )
            {
                if(_mTiles[j][i]->getHitBox().top < player.top
                    && _mTiles[j][i]->getGlobalBounds().top + _tileSize.y < player.top + player.height )
                {
                    return tile = _mTiles[j][i]->getHitBox();
                }
            }
        }
    }
    return tile;
}



const bool Map::checkBottomBool(const sf::FloatRect &player)
{
    int posx;
    posx = floor(player.left /16);

    for(int i=posx; i<posx+1 ; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(_mTiles[j][i] == nullptr )
            {
                return true;
            }
        }
    }
    return false;
}

const sf::FloatRect Map::checkRight(const sf::FloatRect &player) const
{
   sf::FloatRect tile = {};

    for(int i=0; i<80; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(( _mTiles[j][i] != nullptr) &&( _mTiles[j][i]->isSolid()) )
            {
                if(_mTiles[j][i]->getHitBox().left > player.left
                    && (_mTiles[j][i]->getHitBox().left + _tileSize.x) < player.left + player.width)
                {
                    return tile = _mTiles[j][i]->getHitBox();
                }
            }
        }
    }
    return tile;
}

const sf::FloatRect Map::checkLeft(const sf::FloatRect &player) const
{
    sf::FloatRect tile = {};

    for(int i=0; i<80; i++)
    {
        for(int j=0; j<17; j++)
        {
            if(( _mTiles[j][i] != nullptr) &&( _mTiles[j][i]->isSolid()) )
            {
                if(_mTiles[j][i]->getHitBox().left < player.left
                    && (_mTiles[j][i]->getHitBox().left + _mTiles[j][i]->getHitBox().width) < player.left + player.width)
                {
                    return tile = _mTiles[j][i]->getHitBox();
                }
            }
        }
    }
    return tile;
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
