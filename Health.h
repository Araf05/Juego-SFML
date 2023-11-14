#ifndef HEALTH_H
#define HEALTH_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Health: public sf::Drawable
{
    public:
        Health();
        virtual ~Health();

        void initTex();
        void initSprite();
        void initBack();

        const setHurt();
        void recover();

        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        const int _healthPoint = 3;
        int _redHearts = 3;
        sf::Sprite* _spriteHP;
        sf::Texture _texHP;
        sf::Texture _bak;
        sf::RectangleShape _background;
};

#endif // HEALTH_H
