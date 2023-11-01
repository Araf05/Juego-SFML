#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

#include "Tile.h"

class Map: public sf::Drawable
{
    public:
        Map();
        Map(unsigned width, unsigned height, sf::Texture* tile, unsigned tileSize);
        virtual ~Map();

        void addTile(unsigned x, unsigned y);
        void removeTile(unsigned x, unsigned y);

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;


    private:
        sf::Texture _texBak, *_texTile;
        sf::Sprite _bak;
        std::vector< std::vector<Tile*> > _mTiles;

        unsigned _tileSize;
};

#endif // MAP_H
