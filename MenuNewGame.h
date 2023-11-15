#ifndef MENUNEWGAME_H
#define MENUNEWGAME_H
#include <iostream>
#include <SFML/Graphics.hpp>

class MenuNewGame: public sf::Drawable
{
    public:
        MenuNewGame();
        virtual ~MenuNewGame();
        void initFont();
        void initBackground();
        void initText();

        void cmd();
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    private:
        enum class ESTADOS_NEWGAME
        {
            ING_NOMBRE,
            NOMBRE_GUARDADO,
            PRESIONA_ENTER
        };

    private:
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text _ingresar;
        sf::Text *_name;


        sf::RectangleShape _textBox;

        bool _ingresoNombre = false;
        bool _pressEnter = false;
        ESTADOS_NEWGAME _estado= ESTADOS_NEWGAME::ING_NOMBRE;
};
#endif // MENUNEWGAME_H
