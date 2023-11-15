#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Animation.h"

class Enemy: public sf::Drawable
{
    public:
        Enemy(const sf::Vector2f& pos);
        virtual ~Enemy();


        void setDirection( const sf::Vector2f& dir );
        const sf::Vector2f getPosition() const;
        const sf::FloatRect getGlobalBounds() const;
        const sf::FloatRect getHitBox() const;
        bool checkIntersection(const sf::FloatRect &obj);

        void death();

        void cmd();
        void update(float dt);
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        void chase(const sf::Vector2f& playerPos, float dt);
        bool isDead() const;

    private:
        enum class ESTADOS_ENEMY
        {
            IDLE,
            MOVE,
            ATACK,
            DEATH
        };

    private:
        sf::Vector2f _pos;
        float _speed = 1.f;
        sf::Vector2f _vel = { 0.0f, 0.0f };

        sf::Texture _texture;
        sf::Sprite _sprite;
        int _width, _height;
        Hitbox *_hitbox;
        ESTADOS_ENEMY _estado = ESTADOS_ENEMY::IDLE;

        Animation *_animations;
        ESTADOS_ENEMY _currentAnimation = ESTADOS_ENEMY::IDLE;
        void setHitbox();

        int _health;
};

#endif // ENEMY_H
