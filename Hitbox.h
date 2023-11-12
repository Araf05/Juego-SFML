#ifndef HITBOX_H
#define HITBOX_H
#include <SFML/Graphics.hpp>

class Hitbox: public sf::Drawable
{
    public:
        Hitbox( sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);
        virtual ~Hitbox();

        void update();
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        bool checkIntersect(const sf::FloatRect &frect);
        const sf::FloatRect getGlobalBounds() const;

    private:
        sf::Sprite& _sprite;
        sf::RectangleShape _hitbox;
        float _offsetX, _offsetY;
};

#endif // HITBOX_H
