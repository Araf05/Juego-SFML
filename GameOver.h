#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <iostream>
#include <SFML/Graphics.hpp>

class GameOver: public sf::Drawable
{
    public:
        GameOver();
        virtual ~GameOver();
        void initFont();
        void initBackground();
        void initText();

        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        void moveLeft();
        void moveRight();

        int opsContinue();
        bool pressEnter();

    private:
        enum class ESTADOS_GAMEOVER
        {
            IDLE,
            LEFT,
            RIGHT,
            ENTER
        };

    private:
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text _continue, *_options;
        int _time=0, _holdTime=6 , _selectOps;
        bool _opsContinue = false;
        ESTADOS_GAMEOVER _estado = ESTADOS_GAMEOVER::IDLE;
};

#endif // GAMEOVER_H
