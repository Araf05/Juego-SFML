#include "Personaje.h"


Personaje::Personaje( const sf::Vector2f& pos )
    : _pos(pos)
{
    _sprite.setPosition(pos);
    _sprite.setTextureRect( {0,0,48,48} );
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2 , _sprite.getGlobalBounds().height);
    _animations = new Animation[5];
    if(_animations == nullptr) exit(-1);
    _animations[int(ESTADOS_PERSONAJE::IDLE)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Idle.png", 5);
    _animations[int(ESTADOS_PERSONAJE::RUN)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Run.png", 6);
    _animations[int(ESTADOS_PERSONAJE::DEATH)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Death.png", 8, 0);
    _animations[int(ESTADOS_PERSONAJE::JUMP)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Jump.png", 2);
    _animations[int(ESTADOS_PERSONAJE::CROUCH)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Crouch.png", 3, 0);

}

Personaje::~Personaje()
{
    _animations->delAnimation();
    delete [] _animations;
}

void Personaje::setDirection( const sf::Vector2f& dir )
{
    _vel = dir * _speed;
}


void Personaje::cmd()
{
    sf::Vector2f dir = {0.0f, 0.0f};
    _speed=2.f;

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
    {
        if( _estado != ESTADOS_PERSONAJE::JUMP )
        {
            _estado = ESTADOS_PERSONAJE::RUN;
            dir.x -= 1.0f;
        } else if(_estado == ESTADOS_PERSONAJE::JUMP )
        {
            dir.x -= 1.f;
            _speed=5.f;
        }
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
    {
        if(_estado != ESTADOS_PERSONAJE::JUMP )
        {
            _estado = ESTADOS_PERSONAJE::RUN;
            dir.x += 1.0f;
        } else
        {
            dir.x += 1.f;
            _speed=5.f;
        }
    }


    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
    {
        if(_estado != ESTADOS_PERSONAJE::JUMP)
        {
            _estado = ESTADOS_PERSONAJE::JUMP;
            _fJump=12.f;
        }
    }



    if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
    {
        if( (_estado != ESTADOS_PERSONAJE::JUMP) &&(_estado != ESTADOS_PERSONAJE::RUN) )
        {
            _estado = ESTADOS_PERSONAJE::CROUCH;
        }
    }

    _currentAnimation = _estado;
    setDirection(dir);
}

void Personaje::update( float dt)
{

    dt+= 1.f;

    switch(_estado)
    {
        case ESTADOS_PERSONAJE::IDLE:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
        break;
        case ESTADOS_PERSONAJE::RUN:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
            _estado = ESTADOS_PERSONAJE::IDLE;
        break;
        case ESTADOS_PERSONAJE::CROUCH:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
            _estado = ESTADOS_PERSONAJE::IDLE;
        break;
        case ESTADOS_PERSONAJE::JUMP:
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
            _fJump-= 1.0f;
            _vel.y = -_fJump;

        break;
        case ESTADOS_PERSONAJE::DEATH:
        break;
    }

    _sprite.move(_vel);

    if(_vel.x < 0) _sprite.setScale(-1,1);
    if(_vel.x > 0) _sprite.setScale(1,1);

    _pos = {_sprite.getPosition().x,_sprite.getPosition().y};

    _sprite.move(_vel);


    if(_sprite.getGlobalBounds().left < 0 ) _pos.x = _sprite.getOrigin().x;
    if(_sprite.getGlobalBounds().top < 0 ) _pos.y = _sprite.getOrigin().y;

    if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 1280 ) _pos.x = 1280 - _sprite.getOrigin().x;

    if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 550 )
    {
        _pos.y = 550;
        _estado = ESTADOS_PERSONAJE::IDLE;
    }

    _sprite.setPosition(_pos);

}

void Personaje::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

const sf::Vector2f Personaje::getPosition() const
{
    return _pos;
}

void Personaje::setPosition(sf::Vector2f vec)
{
    _sprite.setPosition(vec);
}

const sf::FloatRect Personaje::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}
