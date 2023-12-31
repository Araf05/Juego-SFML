#include "Health.h"

Health::Health()
{
    initTex();
    initSprite();
    initBack();
}

Health::~Health()
{
    delete [] _spriteHP;
}

void Health::initTex()
{
    if(!_texHP.loadFromFile("Stats/heart.png"))
    {
        std::cout<<"Error al cargar heart en Health"<<std::endl;
        exit(-1);
    }
}

void Health::initSprite()
{
    _spriteHP = new sf::Sprite[_healthPoint];
    for(int i=0; i<_healthPoint; i++ )
    {
        _spriteHP[i].setTexture(_texHP);
        _spriteHP[i].setPosition({(float)50+(i*50), 585.f});
    }
}

void Health::initBack()
{

    _background.setSize({1280, 270});
    //_background.setFillColor(sf::Color(209,186,146,240));
    _background.setFillColor(sf::Color(140,137,159,240));



    _background.setPosition(0.f, 544.f);

}

int Health::getRedHeart()
{
    return _redHearts;
}

const int Health::setHurt()
{
    if( _redHearts > 0)
    {
        //std::cout << "Recibiste da�o" << std::endl;
        _redHearts--;
        _spriteHP[_redHearts].setColor(sf::Color::Blue);

    }
    return _redHearts;
}

void Health::recover()
{
    if( _redHearts < 3 )
    {
        _spriteHP[_redHearts].setColor(sf::Color::White);
        _redHearts++;
    }
}

void Health::update(float dt)
{
//    recover();
}


void Health::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background, states);
    for(int i=0; i<_healthPoint; i++)
    {
        target.draw(_spriteHP[i], states);
    }
}
