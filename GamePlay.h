#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Personaje.h"
#include "Enemy.h"
#include "Health.h"
#include "Map.h"
#include "Powerup.h"


class GamePlay: public sf::Drawable
{
    public:
        GamePlay( std::string nombre, int puntos=0  );
        virtual ~GamePlay();

        void checkCollision();
        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states)const override;

        void setName(std::string nombre);

        sf::Vector2f getPlayerPosition() const;
        sf::Vector2f getEnemyPosition() const;

        bool checkPlayerCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& obj);

        void createEnemies(int count);
        void spawnNewEnemies();
        sf::Vector2f getRandomPos();
        bool allEnemiesDead() const;
        void checkEnemyStatus();
        void cleanUpEnemies();
        std::vector<sf::FloatRect> getGlobalBoundsOfEnemies() const;

        void updateEnemies(float dt);
        void chasePlayer(const sf::Vector2f& playerPos, float speed);

        void mapCollisionHandler(sf::Vector2f p, sf::FloatRect t, sf::FloatRect pb);
        int bulletCollisionHandler(std::vector<sf::FloatRect> eb);
        sf::FloatRect enemyCollisionHandler(sf::FloatRect pn, sf::FloatRect eb);

        bool isGameOver();
        int getPoints();


        std::vector<sf::FloatRect> getGlobalBoundsOfPowerUps() const;
        void initializePowerUp();

    private:
        Personaje *_player;
        std::vector<Enemy*> _enemies;
        sf::Texture *_tileText;
        Map *_map;
        Health *_health;
        sf::Text _playerName;

        sf::Font *_font;
        sf::Text *_points;
        sf::Text *_textPoint;
        int _acuPuntos = 0;
        std::string aux;

        Powerup *_powerup;
        bool _playerHasPowerup;


        float _dt;
        int _level;
        int _activeEnemiesCount;

        bool puedeRecibirDmg = false;
        float tiempoDeRecuperacion = 0.0f;
        const float invulnerabilidad = 300.0f;

         bool _gameOver;

        void initPlayer();
        void initMap();
        void initTile();
        void initPoints();
        void initTextPoint();
};

#endif // GAMEPLAY_H
