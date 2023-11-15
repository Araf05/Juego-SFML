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
    setHitbox();
}

Tile::~Tile()
{
    delete [] _hitbox;
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


void Tile::setHitbox()
{
    _hitbox = new Hitbox(_sprite,0+16,0+32,_tileSize.width, _tileSize.height);
}

const sf::FloatRect Tile::getHitBox() const
{
    return _hitbox->getGlobalBounds();
}

const bool Tile::isSolid()
{
    return _solid;
}

void Tile::update(float dt)
{

    _sprite.setPosition(_pos);
    _hitbox->update();
}

void Tile::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
   // target.draw(*_hitbox, states);
}

