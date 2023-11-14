#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Personaje.h"
#include "Enemy.h"
#include "Health.h"
#include "Map.h"


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

        void createEnemies(int count);
        void spawnNewEnemies();
        sf::Vector2f getRandomPos();
        bool allEnemiesDead() const;
        void checkEnemyStatus();
        void cleanUpEnemies();
        sf::FloatRect getGlobalBoundsOfEnemies() const;
        void updateEnemies(float dt);
        void chasePlayer(const sf::Vector2f& playerPos, float speed);

    private:
        Personaje *_player;
        std::vector<Enemy*> _enemies;
        sf::Texture *_tileText;
        Map *_map;
        Health *_health;

        float _dt;
        int _level;
        int _activeEnemiesCount;

        void initPlayer();
        void initMap();
        void initTile();
};

#endif // GAMEPLAY_H
