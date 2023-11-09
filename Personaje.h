#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>

#include "Animation.h"


class Personaje: public sf::Drawable
{
    public:
        Personaje(const sf::Vector2f& pos);

        void setDirection( const sf::Vector2f& dir );
        const sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f vec);
        const sf::FloatRect getGlobalBounds() const;

        void cmd();
        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
        virtual ~Personaje();

        void setEnemyPosition(const sf::Vector2f& playerPos);

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
        float _speed = 2.f;
        float _fJump = 3.f;
        sf::Vector2f _vel = { 0.0f, 0.0f };
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _enemyPosition;
        ESTADOS_PERSONAJE _estado = ESTADOS_PERSONAJE::IDLE;

        Animation *_animations;
        ESTADOS_PERSONAJE _currentAnimation = ESTADOS_PERSONAJE::IDLE;
};

#endif // PERSONAJE_H
