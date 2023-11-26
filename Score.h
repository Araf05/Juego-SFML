#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Score: public sf::Drawable
{
    public:
        Score();
        virtual ~Score();
        void initFont();
        void initBackground();
        void initTitulo();
        void initScore();

        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        bool volverMenu();

    private:
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text *_titulo;
        sf::Text **_score;
        bool _volver;
        int _time = 0;
};

#endif // SCORE_H
