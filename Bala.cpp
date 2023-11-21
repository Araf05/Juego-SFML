#include "Bala.h"

Bala::Bala(const sf::Vector2f& pos, float speedX, float speedY) : _speedX(speedX), _speedY(speedY)
{
    initTexture();
    _sprite.setPosition(pos);
    _sprite.setTexture(_texturaBala);
   // setHitbox();
}

Bala::~Bala()
{
//    delete [] _hitbox;
//    delete [] _sprite;
//    delete [] _textura;
}
void Bala::initTexture()
{
    if(!_texturaBala.loadFromFile("PowerUp/Rocket_1.png"))
    {
        std::cout << "Error al cargar la imagen de bala" << std::endl;
        exit(-1);
    }
}

void Bala::update(float dt)
{
    _sprite.move(_speedX / dt, _speedY / dt);
    _sprite.setTexture(_texturaBala);
    if(_speedX < 0) _sprite.setScale(1,1);

    if(_speedX > 0) _sprite.setScale(-1,1);
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
