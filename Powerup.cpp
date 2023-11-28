#include "Powerup.h"

Powerup::Powerup(const sf::Vector2f& pos)
{
   initTexture();
   _sprite.setPosition(pos);
   _sprite.setTexture(_texturaPowerup);

}

Powerup::~Powerup()
{

}

void Powerup::initTexture()
{
    //Aca va la textura del PowerUp
}

void Powerup::update(float dt)
{

}

sf::FloatRect Powerup::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

void Powerup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

