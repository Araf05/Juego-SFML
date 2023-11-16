#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ArchivoPartidas.h"
#include "Partida.h"
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
        bool savePartida(const int& puntos);


        void cmd(const sf::Event& event);
        void update();
        void draw( sf::RenderWindow& window);
        void leerPartidas();


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
        int  _time=0;
        int _holdTime = 480;


        sf::Text _playerName;
        int _points;
};

#endif // GAME_H
