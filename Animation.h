#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation();
        Animation(int width, int height, const char* a, int nFrame);
        void applyToSprite( sf::Sprite& s) const;
        void update( float dt);

        virtual ~Animation();

    protected:

    private:
        void advance();
        int _nFrames;
        sf::Texture _texture;
        sf::IntRect _frames[8];
        int _iFrame = 0;
        float _time = 0.0f;
        float _holdTime = 5.f;
};

#endif // ANIMATION_H
