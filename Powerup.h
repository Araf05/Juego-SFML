#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Personaje.h"


class Powerup : public sf::Drawable
{

    public:

    Powerup();
    Powerup(const sf::Vector2f& pos);
    virtual ~Powerup();
    void initTexture();
    void update(float dt, Personaje* player);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const;

    sf::Vector2f getRandomPos(int mapWidth, int mapHeight);

    private:

    sf::Sprite _sprite;
    Hitbox *_hitbox;
    void setHitbox();
    sf::Texture _texturaPowerup;


};


#endif // POWERUP_H_INCLUDED
