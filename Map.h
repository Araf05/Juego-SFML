#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <math.h>
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
        bool checkIntersect(const sf::FloatRect &player );

        const sf::FloatRect checkTop(const sf::FloatRect &player) const;
        const sf::FloatRect checkBottom(const sf::FloatRect &player) const;

        const bool checkBottomBool(const sf::FloatRect &player);

        const sf::FloatRect checkRight(const sf::FloatRect &player) const;
        const sf::FloatRect checkLeft(const sf::FloatRect &player) const;

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
