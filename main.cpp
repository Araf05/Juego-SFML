#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MenuNewGame.h"

int main()
{
    const int WIDTH = 1280, HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Juego 1");
    window.setFramerateLimit(60);

    //Game game(WIDTH, HEIGHT);
    MenuNewGame _newGame;

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

        //game.cmd();
        _newGame.cmd();

        //game.update();
        _newGame.update();

        window.clear();

        //game.draw(window);
        window.draw(_newGame);


        window.display();
    }

    return 0;
}
