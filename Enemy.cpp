#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& pos)
    : _pos(pos)
{
    _sprite.setPosition(pos);
    _width = 64;
    _height = 80;
    _sprite.setTextureRect( {0,0,_width,_height} );
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2 , _sprite.getGlobalBounds().height);
    setHitbox();
    _animations = new Animation[4];
    if(_animations == nullptr) exit(-1);
    _animations[int(ESTADOS_ENEMY::IDLE)] = Animation(64,80,"Ghost/ghost-idle.png", 7);
    _animations[int(ESTADOS_ENEMY::MOVE)] = Animation(64,80,"Ghost/ghost-idle.png", 4);
    _animations[int(ESTADOS_ENEMY::DEATH)] = Animation(64,80,"Ghost/ghost-atack.png", 7, 0);
    _animations[int(ESTADOS_ENEMY::ATACK)] = Animation(64,80,"Ghost/ghost-atack.png", 6 );

}

Enemy::~Enemy()
{
    _animations->delAnimation();
    delete [] _animations;
    delete _hitbox;
}

void Enemy::setHitbox()
{
    _hitbox = new Hitbox(_sprite,(_width/4)+3,(_height/4)+4,(_width/2)-8, (_height/2)-6);
}

const sf::FloatRect Enemy::getHitBox() const
{
    return _hitbox->getGlobalBounds();
}

bool Enemy::checkIntersection(const sf::FloatRect &obj)
{
    return _hitbox->checkIntersect(obj);
}

void Enemy::setDirection( const sf::Vector2f& dir )
{
    _vel = dir * _speed;
}


void Enemy::cmd()
{
    sf::Vector2f dir = {0.0f, 0.0f};
    _speed=1.f;

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
    {
         _estado = ESTADOS_ENEMY::MOVE;
        dir.x -= 1.0f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
    {
        _estado = ESTADOS_ENEMY::MOVE;
        dir.x += 1.0f;
    }


    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        if( _estado != ESTADOS_ENEMY::MOVE )
        {
            _estado = ESTADOS_ENEMY::ATACK;
        }
    }

    _currentAnimation = _estado;
    setDirection(dir);
}

void Enemy::update( float dt)
{

    dt+= 0.2f;

    switch(_estado)
    {
        case ESTADOS_ENEMY::IDLE:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
        break;
        case ESTADOS_ENEMY::MOVE:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
            _estado = ESTADOS_ENEMY::IDLE;
        break;
        case ESTADOS_ENEMY::ATACK:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
            _estado = ESTADOS_ENEMY::IDLE;
        break;

        case ESTADOS_ENEMY::DEATH:
        break;
    }

    _sprite.move(_vel);

    if(_vel.x < 0) _sprite.setScale(1,1);
    if(_vel.x > 0) _sprite.setScale(-1,1);

    _pos = {_sprite.getPosition().x,_sprite.getPosition().y};

    _sprite.move(_vel);


    if(_sprite.getGlobalBounds().left < 0 ) _pos.x = _sprite.getOrigin().x;
    if(_sprite.getGlobalBounds().top < 0 ) _pos.y = _sprite.getOrigin().y;

    if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 1280 ) _pos.x = 1280 - _sprite.getOrigin().x;

    if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 568 )
    {
        _pos.y = 568;
        _estado = ESTADOS_ENEMY::IDLE;
    }

    _sprite.setPosition(_pos);
    _hitbox->update();

}


void Enemy::chase(const sf::Vector2f& playerPos, float dt)
{

    sf::Vector2f direction = playerPos - _pos;
    float distanceToPlayer = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distanceToPlayer > 0)
    {
        direction /= distanceToPlayer;

        float chaseSpeed = 0.5f;
        _vel = direction * chaseSpeed;

        if (distanceToPlayer <= chaseSpeed * dt)
        {
            _pos = playerPos;
            _estado = ESTADOS_ENEMY::IDLE;
        }
        else
        {
            _pos += _vel;
        }
    }
}



void Enemy::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    //target.draw(*_hitbox, states);
}

const sf::Vector2f Enemy::getPosition() const
{
    return {(_pos.x - _width/2), (_pos.y - _height) };;
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

bool Enemy::isDead() const {
    return _health <= 0;
}

void Enemy::death()
{
    _estado = ESTADOS_ENEMY::DEATH;
}
