#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemy.h"
#include "Map.h"
#include "Tile.h"

class GamePlay: public sf::Drawable
{
    public:
        GamePlay();
        virtual ~GamePlay();

        void checkCollision();
        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states)const override;


        sf::Vector2f getPlayerPosition() const;
        sf::Vector2f getEnemyPosition() const;

        bool checkPlayerCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& obj);
      //  bool checkPlayerTileCollision(const sf::FloatRect& playerBounds);

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
