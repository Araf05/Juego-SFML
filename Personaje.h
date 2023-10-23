#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>

#include "Animation.h"


class Personaje: public sf::Drawable
{
    public:
        Personaje(const sf::Vector2f& pos);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        void setDirection( const sf::Vector2f& dir );

        void cmd();
        void update(float dt);
//        void setIdle();

    protected:

    private:
        enum class ESTADOS_PERSONAJE
        {
            IDLE,
            RUN,
            JUMP,
            CROUCH,
            DEATH
        };

    private:
        sf::Vector2f _pos;
        float _speed = 5.0f;
        float _fJump = 3.f;
        sf::Vector2f _vel = { 0.0f, 0.0f };
        sf::Texture _texture;
        sf::Sprite _sprite;
        ESTADOS_PERSONAJE _estado = ESTADOS_PERSONAJE::IDLE;

        Animation _animations[5];
        ESTADOS_PERSONAJE _currentAnimation = ESTADOS_PERSONAJE::IDLE;
};

#endif // PERSONAJE_H
