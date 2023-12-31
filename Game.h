#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ArchivoPuntajes.h"
#include "Puntaje.h"
#include "Menu.h"
#include "MenuNewGame.h"
#include "GamePlay.h"
#include "Credit.h"
#include "Score.h"


class Game
{
    public:
        Game(const int& width, const int& height);
        virtual ~Game();

        void initMenu(const int& width, const int& height);
        void initNewGame();
        void initGamePlay(std::string nombre, int puntos = 0);
        void initCredit();
        void initScore();

        void setEstadoMenu(int& ops);
        bool saveScore(const int& puntos);
        bool updateFileScore(Puntaje nuevoPuntaje);
        void handlerState();


        void cmd(const sf::Event& event);
        void update();
        void draw( sf::RenderWindow& window);



    private:
        enum class ESTADOS_GAME
        {
            MENU,
            NEWGAME,
            GAMEPLAY,
            SCORE,
            CREDITS,
            QUIT
        };

    private:
        ESTADOS_GAME _estado = ESTADOS_GAME::MENU;
        Menu *_menu;
        GamePlay *_runGame;
        MenuNewGame *_newGame;
        Credit *_credits;
        Score *_score;
        int  _time=0;
        int _holdTime = 480;
        int _width, _height;


        std::string _playerName;
        int _points;
};

#endif // GAME_H
