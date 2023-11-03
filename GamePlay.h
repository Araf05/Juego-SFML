#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemy.h"
#include "Map.h"

class GamePlay
{
    public:
        GamePlay();
        virtual ~GamePlay();

        void checkCollision();
        void cmd();
        void update();
        void draw( sf::RenderWindow& window);

    private:
        Personaje *_player;
        Enemy *_enemy;
        sf::Texture *_tileText;
        Map *_map;
        float _dt;
        int _level;

        void initPlayer();
        void initMap();
        void initTile();
};

#endif // GAMEPLAY_H
