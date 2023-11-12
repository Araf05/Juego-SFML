#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemy.h"
#include "Map.h"

class GamePlay
{
    public:
        GamePlay();
        virtual ~GamePlay();


        void cmd();
        void update();
        void draw( sf::RenderWindow& window);

        sf::Vector2f getPlayerPosition() const;
        sf::Vector2f getEnemyPosition() const;

        sf::Clock _timer;

        sf::Text _timerText;
        sf::Font _font;

        bool checkPlayerEnemyCollision();

    private:
        Personaje *_player;
        Enemy *_enemy;
        sf::Texture *_tileText;
        Map *_map;
        float _dt;
        int _level;
        float _renderDt;

        void initPlayer();
        void initMap();
        void initTile();
};

#endif // GAMEPLAY_H
