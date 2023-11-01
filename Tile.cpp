#include "Tile.h"

Tile::Tile()
    : _damaging(false)
{}

Tile::Tile(sf::Texture* texture, sf::IntRect texRect, bool damaging)
    : _damaging(damaging)
{
    _sprite.setTexture(*texture);
    _sprite.setTextureRect(texRect);
}

Tile::~Tile()
{
    //dtor
}

void Tile::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}
