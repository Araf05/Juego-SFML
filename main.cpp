#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "GamePlay.h"

int main()
{
    const int WIDTH = 1280, HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Juego 1");
    window.setFramerateLimit(60);

    Game game(WIDTH, HEIGHT);

   // GamePlay gamePlay;

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

        //gamePlay.cmd();
        game.cmd();

        //gamePlay.update();
        game.update();


        window.clear();

        //gamePlay.draw(window);
        game.draw(window);


        window.display();
    }

    return 0;
}
