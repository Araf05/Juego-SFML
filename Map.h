#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Tile.h"

class Map: public sf::Drawable
{
    public:
        Map();
        Map(int height, int width, sf::Texture* tile, sf::Vector2i tSize);
        virtual ~Map();

        void addTile(int x, int y, sf::Texture* vTex, int indexText);
        void removeTile(int x, int y);
        Tile getTile(int posX, int posY);

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;


    private:
        sf::Texture _texBak, *_texTile;
        sf::Sprite _bak;
        sf::Vector2i _tileSize;

        Tile ***_mTiles;
        int _filas, _cols;
};

#endif // MAP_H
