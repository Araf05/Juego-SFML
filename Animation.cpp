#include "Animation.h"

Animation::Animation(){}

Animation::Animation(int width, int height, const char* a, int nFrame, bool repeat)
{
    _nFrames = nFrame;
    _texture.loadFromFile(a);
    for(int i=0; i<nFrame ; i++)
    {
        _frames[i] = { i*width , 0, width, height };
    }
    _repeat = repeat;
}


Animation::~Animation()
{
    //dtor
}

void Animation::advance()
{

    if(_repeat)
    {
        if(++_iFrame >= _nFrames) _iFrame = 0;
    } else
    {
        if(++_iFrame >= _nFrames) _iFrame = _nFrames-1;
    }
}

void Animation::applyToSprite( sf::Sprite& s) const
{
    s.setTexture(_texture);
    s.setTextureRect(_frames[_iFrame]);
}

void Animation::update(float dt)
{
    _time += dt;
    while( _time >= _holdTime)
    {
        _time -= _holdTime;
        advance();
    }
}

