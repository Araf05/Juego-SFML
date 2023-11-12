#include "Bala.h"
#include <iostream>

Bala::Bala(const sf::Vector2f& pos, float speedX, float speedY) : _speedX(speedX), _speedY(speedY)
{
    _bala.setSize(sf::Vector2f(10,5));
    _bala.setFillColor(sf::Color::Red);
    _bala.setPosition(pos);
}

void Bala::update(float _dt)
{
    _bala.move(_speedX * _dt , -_speedY * _dt );
}

sf::FloatRect Bala::getGlobalBounds() const
{
    return _bala.getGlobalBounds();
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_bala, states);
}
