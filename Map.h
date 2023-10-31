#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

class Map: public sf::Drawable
{
    public:
        Map();
        virtual ~Map();

        void cmd();
        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;


    private:
        sf::Texture _texture;
        sf::Sprite _bak;
        int _mDimension;
};

#endif // MAP_H
