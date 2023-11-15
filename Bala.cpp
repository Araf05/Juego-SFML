#include <iostream>
#include "Bala.h"

Bala::Bala(const sf::Vector2f& pos, float speedX, float speedY) : _speedX(speedX), _speedY(speedY)
{
//    _bala.setSize(sf::Vector2f(10,5));
//    _bala.setFillColor(sf::Color::Red);
//    _bala.setPosition(pos);
    if(!texturaBala.loadFromFile("Extras/bullet.png"))std::cout << "Error al cargar la imagen de bala" << std::endl;
    _sprite.setPosition(pos);
    _sprite.setTexture(texturaBala);
   // _sprite.scale(10, 10);
   // setHitbox();

}

void Bala::update(float dt)
{
    _sprite.move(_speedX / dt, _speedY / dt);
}

sf::FloatRect Bala::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
   // target.draw(*_hitbox, states);
}

//void Bala::setHitbox()
//{
//    _hitbox = new Hitbox(_sprite, 10/4, 5/4, 5, 5/2);
//}
