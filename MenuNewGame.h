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
        void initName();

        sf::Text getName();

        void cmd(const sf::Event& event);
        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        bool ingreso = false;

        std::string getNombre() const;

//    private:
//        enum class ESTADOS_NEWGAME
//        {
//            ING_NOMBRE,
//            NOMBRE_GUARDADO,
//            PRESIONA_ENTER
//        };

    private:
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;
        sf::Font *_font;
        sf::Text _ingresar;
        sf::Text *_name;
        std::string nombre;


        sf::RectangleShape _textBox;

//        bool _ingresoNombre = false;
//        bool _pressEnter = false;
       // ESTADOS_NEWGAME _estado= ESTADOS_NEWGAME::ING_NOMBRE;
};
#endif // MENUNEWGAME_H
