#include "Powerup.h"
#include <iostream>
#include <random>

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
    if(!_texturaPowerup.loadFromFile("PowerUp/heart.png"))
    {
        std::cout << "Error al cargar la imagen de corazon" << std::endl;
        exit(-1);
    }
}

void Powerup::update(float dt, Personaje* player)
{

}


sf::Vector2f Powerup::getRandomPos(int mapWidth, int mapHeight)
{
    std::random_device rd;
    std::mt19937 gen(rd()); //Mersenne Twister (generador de numeros pseudoaleatorios)
    std::uniform_int_distribution<int> distribX(0, mapWidth - 1);
    std::uniform_int_distribution<int> distribY(0, mapHeight - 1);
    int randomX = distribX(gen);
    int randomY = distribY(gen);

    return sf::Vector2f(randomX,randomY);

}

sf::FloatRect Powerup::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

void Powerup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

