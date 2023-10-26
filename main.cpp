#include <SFML/Graphics.hpp>
#include "GamePlay.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Juego 1");
    window.setFramerateLimit(60);

    GamePlay gamePlay;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        gamePlay.cmd();

        gamePlay.update();

        window.clear();
        gamePlay.draw(window);

        window.display();
    }

    return 0;
}
