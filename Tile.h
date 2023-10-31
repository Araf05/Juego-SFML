#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile: public sf::Drawable
{
    public:
        Tile(sf::Texture& texture, sf::IntRect texRect, bool damaging = false);
        virtual ~Tile();

        const sf::FloatRect getGlobalBounds() const;

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    private:
        sf::Sprite _sprite;
        const bool _damaging;

};

#endif // TILE_H
