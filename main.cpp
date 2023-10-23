#include <SFML/Graphics.hpp>
#include "Personaje.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Juego 1");
    window.setFramerateLimit(60);
    float dt= 0.0f;

    Personaje player({750,600});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.cmd();

        player.update(dt);

        window.clear();
        window.draw(player);

        window.display();
    }

    return 0;
}
