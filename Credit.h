#ifndef CREDIT_H
#define CREDIT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Credit: public sf::Drawable
{
    public:
        Credit();
        virtual ~Credit();
        void initFont();
        void initBackground();
        void initText();
        void initPlayers();
        void initAnimation();

        bool volverMenu();

        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    private:
        sf::Texture _background;
        sf::Sprite _bak, _player[2];
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text *_creditT;
        bool _volver;
        Animation *_animation;
        int _time;

};

#endif // CREDIT_H
