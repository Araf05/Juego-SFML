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
        const setHurt();
        void recover();


        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        const int _healthPoint = 3;
        int _redHearts = 3;
        sf::Sprite* _spriteHP;
        sf::Texture _texHP;
};

#endif // HEALTH_H
