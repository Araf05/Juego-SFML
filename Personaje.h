#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Hitbox.h"
#include "Animation.h"


class Personaje: public sf::Drawable
{
    public:
        Personaje(const sf::Vector2f& pos);

        void setVelocity( const sf::Vector2f& dir );
        sf::Vector2f getVelocity();
        const sf::Vector2f getPosition() const;
        const sf::FloatRect getNextPos() const;

        void setPosition(sf::Vector2f vec);
        void setQuiet();
        void setFall(const float& dt);

        const sf::FloatRect getGlobalBounds() const;
        const sf::FloatRect getHitBox() const;
        bool checkIntersection(const sf::FloatRect &obj);

        void cmd();
        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        virtual ~Personaje();

    private:
        enum class ESTADOS_PERSONAJE
        {
            IDLE,
            RUN,
            JUMP,
            CROUCH,
            DEATH,
            FALL
        };

    private:
        sf::Vector2f _pos;
        sf::FloatRect _nextPos;

        float _speed = 2.f;
        float _fJump = 3.f;
        sf::Vector2f _vel = { 0.0f, 0.0f };
        int _isFall = 0;
        float _time=0;

        sf::Texture _texture;
        sf::Sprite _sprite;
        int _width, _height;
        Hitbox *_hitbox;
        ESTADOS_PERSONAJE _estado = ESTADOS_PERSONAJE::IDLE;
        ESTADOS_PERSONAJE _estadoAnterior = ESTADOS_PERSONAJE::IDLE;

        Animation *_animations;
        ESTADOS_PERSONAJE _currentAnimation = ESTADOS_PERSONAJE::IDLE;
        void setHitbox();
};

#endif // PERSONAJE_H
