#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    const int WIDTH = 1280, HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gunman v0.1");
    window.setFramerateLimit(60);

    Game game(WIDTH, HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if( event.Event::key.code == sf::Keyboard::Escape )
                window.close();
        }

        game.cmd(event);

        game.update();

        window.clear();

        game.draw(window);

        window.display();
    }

    return 0;
}
