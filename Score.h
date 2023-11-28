#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Puntaje.h"
#include "ArchivoPuntajes.h"

class Score: public sf::Drawable
{
    public:
        Score();
        virtual ~Score();
        void initFont();
        void initBackground();
        void initTitulo();
        void initScore();

        void initCantReg();
        void initVecPuntajes();
        void updateScore();


        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        bool volverMenu();

    private:
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text *_titulo, **_score;
        int _filas, _cols, _cantReg, _time = 0;
        float _colum1=200, _colum2=450, _colum3=820, _scoreFila=200;
        bool _volver;
        Puntaje *_vecPuntajes;
};

#endif // SCORE_H
