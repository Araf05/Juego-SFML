#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Hitbox.h"


class Powerup : public sf::Drawable
{

    public:

    Powerup();
    Powerup(const sf::Vector2f& pos);
    virtual ~Powerup();
    void initTexture();
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const;

    private:

    sf::Sprite _sprite;
    Hitbox *_hitbox;
    void setHitbox();
    sf::Texture _texturaPowerup;


};


#endif // POWERUP_H_INCLUDED
