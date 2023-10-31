#include "Map.h"

Map::Map()
{
     _bak.setPosition({0,0});
     _texture.loadFromFile("Background/night-town.png");
     _bak.setTexture(_texture);
    // _bak.setColor(sf::Color::Blue);
     _bak.scale(3.5f, 3.5f);
}

Map::~Map()
{
    //dtor
}

void Map::cmd()
{

}
void Map::update(float dt)
{

}
void Map::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
}
