#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class Bala : public sf::Drawable
{

    public:
    Bala();
    Bala(const sf::Vector2f& pos, float speedX, float speedY);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const;

    private:
    sf::Sprite _sprite;
    float _speedX;
    float _speedY;
    Hitbox *_hitbox;
    void setHitbox();
    sf::Texture texturaBala;

};


#endif // BALA_H_INCLUDED
