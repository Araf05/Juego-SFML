#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

#include "Tile.h"

class Map: public sf::Drawable
{
    public:
        Map();
        virtual ~Map();

        void addTile(unsigned x, unsigned y);
        void removeTile(unsigned x, unsigned y);

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;


    private:
        sf::Texture _texture;
        sf::Sprite _bak;
        Tile *_mTiles;
};

#endif // MAP_H
