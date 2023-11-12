#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

#include <SFML/Graphics.hpp>

class Bala : public sf::RectangleShape {

public:
    Bala(const sf::Vector2f& pos, float speedX, float speedY);

    void update(float _dt);
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape _bala;
    float _speedX;
    float _speedY;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // BALA_H_INCLUDED
