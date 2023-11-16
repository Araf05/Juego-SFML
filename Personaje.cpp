#include "Personaje.h"


Personaje::Personaje( const sf::Vector2f& pos )
    : _pos(pos)
{
    _sprite.setPosition(pos);
    _width = 48;
    _height = 48;
    _sprite.setTextureRect( {0,0,_width,_height} );
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2 , _sprite.getGlobalBounds().height);
    setHitbox();
    _animations = new Animation[6];
    if(_animations == nullptr) exit(-1);
    _animations[int(ESTADOS_PERSONAJE::IDLE)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Idle.png", 5);
    _animations[int(ESTADOS_PERSONAJE::RUN)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Run.png", 6);
    _animations[int(ESTADOS_PERSONAJE::DEATH)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Death.png", 8, 0);
    _animations[int(ESTADOS_PERSONAJE::JUMP)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Jump.png", 2);
    _animations[int(ESTADOS_PERSONAJE::CROUCH)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Crouch.png", 3, 0);
    _animations[int(ESTADOS_PERSONAJE::FALL)] = Animation(48,48,"CHARACTER_SPRITES/Blue/Blue_Idle.png", 5);

}

Personaje::~Personaje()
{
    _animations->delAnimation();
    delete [] _animations;
    delete [] _hitbox;
}

sf::Vector2f Personaje::getVelocity()
{
    return _vel;
}

void Personaje::setVelocity( const sf::Vector2f& dir )
{
    _vel = dir * _speed;
    _nextPos = _hitbox->getGlobalBounds();
    _nextPos.left += _vel.x;
    _nextPos.top += _vel.y;
}

float Personaje::getJump() const
{
    return _fJump;
}


void Personaje::cmd()
{

    sf::Vector2f dir = {0.0f, 0.0f};
    _speed=2.f;
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
    {
        if( _estado != ESTADOS_PERSONAJE::JUMP && _estado != ESTADOS_PERSONAJE::FALL && _estado != ESTADOS_PERSONAJE::DEATH )
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
        if(_estado != ESTADOS_PERSONAJE::JUMP && _estado != ESTADOS_PERSONAJE::FALL&& _estado != ESTADOS_PERSONAJE::DEATH )
        {
            _estado = ESTADOS_PERSONAJE::RUN;
            dir.x += 1.0f;
        } else if (_estado == ESTADOS_PERSONAJE::JUMP)
        {
            dir.x += 1.f;
            _speed=5.f;
        }
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
    {
        if(_estado != ESTADOS_PERSONAJE::JUMP && _estado != ESTADOS_PERSONAJE::DEATH)
        {
            _estado = ESTADOS_PERSONAJE::JUMP;
            dir.y += 1.0f;
            _fJump=16.f;
        }
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
    {
        if( (_estado != ESTADOS_PERSONAJE::JUMP) &&(_estado != ESTADOS_PERSONAJE::RUN) && _estado != ESTADOS_PERSONAJE::DEATH )
        {
            _estado = ESTADOS_PERSONAJE::CROUCH;
        }
    }

    if(dir.x != 0 || dir.y != 0){
        _previousPosition = dir;
    }

    _currentAnimation = _estado;
    setVelocity(dir);
}


void Personaje::setHitbox()
{
    _hitbox = new Hitbox(_sprite,_width/4,_height/4,_width/2, _height/2);
}

const sf::FloatRect Personaje::getHitBox() const
{
    return _hitbox->getGlobalBounds();
}

bool Personaje::checkIntersection(const sf::FloatRect &obj)
{
    return _hitbox->checkIntersect(obj);
}



const sf::FloatRect Personaje::getNextPos() const
{
    return _nextPos;
}

void Personaje::setFall(const float& dt)
{
    _time+=dt;
    _isFall++;
    if((_estado != ESTADOS_PERSONAJE::JUMP) && (_isFall >=20 || _time>3600) )
    {
        _estado = ESTADOS_PERSONAJE::FALL;
        _isFall=0;
        _time=0;
    }

    if(_time > 3600) _time=0;

}

void Personaje::setQuiet()
{
    _estado = ESTADOS_PERSONAJE::IDLE;
    _isFall= 0;
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
            _animations[int(_currentAnimation)].update(dt);
            _animations[int(_currentAnimation)].applyToSprite(_sprite);
        break;
        case ESTADOS_PERSONAJE::FALL:
            _vel.y += 9.f;
//            _animations[int(_currentAnimation)].update(dt);
//            _animations[int(_currentAnimation)].applyToSprite(_sprite);
        break;
    }

    _sprite.move(_vel);

    /// flip
    if(_vel.x < 0) _sprite.setScale(-1,1);

    if(_vel.x > 0) _sprite.setScale(1,1);


    _pos = {_sprite.getPosition().x,_sprite.getPosition().y};

    _sprite.move(_vel);


    if(_sprite.getGlobalBounds().left < 0 ) _pos.x = _sprite.getOrigin().x;
    if(_sprite.getGlobalBounds().top < 0 ) _pos.y = _sprite.getOrigin().y;

    if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 1280 ) _pos.x = 1280 - _sprite.getOrigin().x;

    if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 568 )
    {
        _pos.y = 568;
        _estado = ESTADOS_PERSONAJE::IDLE;
    }

    _hitbox->update();


    _sprite.setPosition(_pos);

    for(auto& bala : _balas) bala.update(dt);

    if(estaDisparando)
    {
        _tiempoUltimoDisparo += dt;
        if(_tiempoUltimoDisparo >= _tiempoRecarga)
            {
                estaDisparando = false;
            }
    }


}

void Personaje::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    for(const auto& bala : _balas) target.draw(bala, states);
   // target.draw(*_hitbox, states);
}

const sf::Vector2f Personaje::getPosition() const
{
    return {(_pos.x - _width/2), (_pos.y - _height) };
}

void Personaje::setPosition(sf::Vector2f vec)
{
    _sprite.setPosition(vec);
}

const sf::FloatRect Personaje::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}


void Personaje::disparar()
{

    if(!estaDisparando){
        if(_vel.x > 0 || (_vel.x == 0 && _previousPosition.x > 0)) {
     Bala balaR( _pos - sf::Vector2f(-10.0f, 30.0f), 30.0f, 0.0f);
     _balas.push_back(balaR);
    } else if(_vel.x < 0 || (_vel.x == 0 && _previousPosition.x < 0)) {
     Bala balaL( _pos + sf::Vector2f(-10.0f, -30.0f), -30.0f, 0.0f);
     _balas.push_back(balaL);
    }
    estaDisparando = true;
    _tiempoUltimoDisparo = 0.0f;

    std::cout << "size " << _balas.size() << std::endl;

    if(_balas.size() >= 10)
    {
        _balas.clear();
    }
}

}

std::vector<sf::FloatRect> Personaje::getGlobalBoundsBullets()
{
    std::vector<sf::FloatRect> allBulletsBounds;
    if(_balas.empty()) return std::vector<sf::FloatRect> {};

    for(int i = 0; i < (int)_balas.size(); i++)
    {
        sf::FloatRect bulletBounds = _balas[i].getGlobalBounds();
        allBulletsBounds.push_back(bulletBounds);
    }

    return allBulletsBounds;
}

void Personaje::isDead()
{
    _estado = ESTADOS_PERSONAJE::DEATH;
}
