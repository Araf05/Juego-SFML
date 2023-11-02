#include "Tile.h"

//Tile::Tile()
//    : _damaging(false)
//{}

Tile::Tile(sf::Vector2f pos, sf::Texture* texture, sf::IntRect texRect, bool damaging)
    : _damaging(damaging)
{
    setPosition(pos);
    _tileSize = texRect;
    _sprite.setTexture(*texture);
    _sprite.setTextureRect(_tileSize);
}

Tile::~Tile()
{
    //dtor
}

void Tile::setPosition(sf::Vector2f pos)
{
    _pos = pos;
}

void Tile::update(float dt)
{
    _sprite.setPosition(_pos);
}

void Tile::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}
