#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GamePlay.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Juego 1");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    GamePlay gamePlay;

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

        gamePlay.cmd();
        //menu.cmd();

        gamePlay.update();
        //menu.update();

        window.clear();

        gamePlay.draw(window);
        //window.draw(menu);

        window.display();
    }

    return 0;
}
