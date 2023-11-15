#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "MenuNewGame.h"
#include "GamePlay.h"


class Game
{
    public:
        Game(const int& width, const int& height);
        virtual ~Game();

        void initMenu(const int& width, const int& height);
        void initGamePlay();
        void setEstado(int& ops);

        void cmd();
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
        bool _hayPartidasGuardadas=false;
};

#endif // GAME_H
