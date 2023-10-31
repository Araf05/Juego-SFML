#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& pos)
    : _pos(pos)
{
    _sprite.setPosition(pos);
    _sprite.setTextureRect( {0,0,64,80} );
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2 , _sprite.getGlobalBounds().height);
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

    if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 1200 ) _pos.x = 1200 - _sprite.getOrigin().x;

    if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 800 )
    {
        _pos.y = 800;
        _estado = ESTADOS_ENEMY::IDLE;
    }

    _sprite.setPosition(_pos);

}

void Enemy::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

const sf::Vector2f Enemy::getPosition() const
{
    return _pos;
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}
