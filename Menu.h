#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu: public sf::Drawable
{
    public:
        Menu(const float& width, const float& height,const int& hayArchivo);
        void initFont();
        void initBackground();
        void initOps(const float& width, const float& height, const int& hayArchivo);
        void moveUp();
        void moveDown();

        void cmd();
        void update(const int& dt, int& ops);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;


        virtual ~Menu();
    private:
        enum class ESTADOS_MENU
        {
            IDLE,
            UP,
            DOWN,
            ENTER
        };

    private:
        sf::Font _font;
        sf::Texture _background;
        sf::Sprite _bak;
        sf::RectangleShape _blackRec;

        bool _hayArchivo= false;
        int _cantOps= 5;
        int _selectOps;
        sf::Text *_options;
        ESTADOS_MENU _estado = ESTADOS_MENU::IDLE;
        float _time=0;
        float _holdTime = 6;

};

#endif // MENU_H
