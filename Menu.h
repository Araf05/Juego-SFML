#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu: public sf::Drawable
{
    public:
        Menu(float width, float height);
        void initOps(const float& width, const float& height);
        void moveUp();
        void moveDown();

        void cmd();
        void update();
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
        const int _cantOps = 5;
        int _selectOps;
        sf::Text *_options;
        ESTADOS_MENU _estado = ESTADOS_MENU::IDLE;

        int tic = 0;
};

#endif // MENU_H
