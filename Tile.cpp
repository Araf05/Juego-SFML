#include "Tile.h"

Tile::Tile()
    : _damaging(false), _solid(true)
{}

Tile::Tile(sf::Vector2f pos, sf::Texture* texture, sf::IntRect texRect, bool solid, bool damaging)
    : _damaging(damaging) , _solid(true)
{
    setPosition(pos);
    _tileSize = texRect;
    _sprite.setTexture(*texture);
    _sprite.setTextureRect(_tileSize);
    _solid = solid;
}

Tile::~Tile()
{
    //dtor
}

void Tile::setPosition(sf::Vector2f pos)
{
    _pos = pos;
}

const sf::Vector2f Tile::getPosition()
{
    return _pos;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

const bool Tile::isSolid()
{
    return _solid;
}

void Tile::update(float dt)
{
    _sprite.setPosition(_pos);
}

void Tile::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

