#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

class Map
{
    public:
        Map();
        virtual ~Map();



    private:
        sf::Texture _texture;
        sf::Sprite _bak;
        int _mDimension;
};

#endif // MAP_H
