#ifndef HEALTH_H_INCLUDED
#define HEALTH_H_INCLUDED

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

        int getRedHeart();
        const setHurt();
       // void recover();

        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        const int _healthPoint = 3;
        int _redHearts = 3;
        float dt;
        sf::Sprite* _spriteHP;
        sf::Texture _texHP;
        sf::Texture _bak;
        sf::RectangleShape _background;
};





#endif // HEALTH_H_INCLUDED
