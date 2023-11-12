#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

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

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    private:
        sf::Sprite _sprite;
        sf::Vector2f _pos;
        sf::IntRect _tileSize;

        const bool _damaging;
        bool _solid;

        sf::FloatRect _collisionBox;

};

#endif // TILE_H
