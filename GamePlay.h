#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Enemy.h"

class GamePlay
{
    public:
        GamePlay();
        virtual ~GamePlay();

        void cmd();
        void update();
        void draw( sf::RenderWindow& window);

    private:
        Personaje _player;
        Enemy _enemy;
        float _dt;
};

#endif // GAMEPLAY_H
