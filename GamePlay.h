#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include "Personaje.h"

class GamePlay
{
    public:
        GamePlay();
        virtual ~GamePlay();

        void cmd();
        void update(float dt);
        void draw( sf::RenderWindow& window);

    protected:

    private:
        Personaje _player;
};

#endif // GAMEPLAY_H
