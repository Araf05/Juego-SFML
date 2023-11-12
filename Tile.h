#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class Tile: public sf::Drawable
{
    public:
        Tile();
        Tile(sf::Vector2f pos, sf::Texture* texture, sf::IntRect texRect,bool solid, bool damaging = false);
        virtual ~Tile();

        const sf::FloatRect getGlobalBounds() const;
        void setPosition(sf::Vector2f pos);
        const sf::Vector2f getPosition();
        const bool isSolid();
        const sf::FloatRect getHitBox() const;

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    private:
        sf::Sprite _sprite;
        sf::Vector2f _pos;
        sf::IntRect _tileSize;
        Hitbox *_hitbox;

        const bool _damaging;
        bool _solid;
        void setHitbox();


};

#endif // TILE_H
