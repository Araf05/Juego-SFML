#include "Hitbox.h"

Hitbox::Hitbox( sf::Sprite &sprite, float offsetX, float offsetY, float width, float height)
    : _sprite(sprite), _offsetX(offsetX), _offsetY(offsetY)
{
    _hitbox.setPosition( (_sprite.getPosition().x - _sprite.getGlobalBounds().width/2) + offsetX, _sprite.getPosition().y + offsetY );
    _hitbox.setSize(sf::Vector2f( width, height ));
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setOutlineThickness(1.f);
    _hitbox.setOutlineColor(sf::Color::White);
}

Hitbox::~Hitbox()
{
    //dtor
}

void Hitbox::update()
{
    _hitbox.setPosition( (_sprite.getPosition().x - _sprite.getGlobalBounds().width/2)+ _offsetX, (_sprite.getPosition().y - _sprite.getGlobalBounds().height) + _offsetY );
}


void Hitbox::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_hitbox, states);
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
    return _hitbox.getGlobalBounds();
}

bool Hitbox::checkIntersect(const sf::FloatRect &frect)
{
    return _hitbox.getGlobalBounds().intersects(frect);
}
