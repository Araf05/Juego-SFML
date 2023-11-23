#include "Credit.h"

Credit::Credit()
{
    initBackground();
    initFont();
    initText();
    initPlayers();
    initAnimation();
    _volver = false;
    _time=0;
}

Credit::~Credit()
{
    delete [] _creditT;
    delete [] _font;
    delete [] _animation;
}

void Credit::initBackground()
{
    if(!_background.loadFromFile("Background/bakMenu.jpeg"))
    {
        std::cout<<"Error al cargar png en Menu"<<std::endl;
        exit(-1);
    }
    _bak.setTexture(_background);
    _bak.setScale(1.25,1.15);
    _bak.setPosition({0,-300});

    _blackRec.setFillColor(sf::Color(0,0,25,180));
    _blackRec.setSize({1280,800});
    _blackRec.setPosition({0,0});
}

void Credit::initFont()
{
    _font = new sf::Font;
    if(_font == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en Font, Menu New Game"<<std::endl;
        exit(-1);
    }
    if(!_font->loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Menu"<<std::endl;
        exit(-1);
    }
}

void Credit::initText()
{
    _creditT = new sf::Text[3];
    for(int i=0; i<3; i++ )
    {
        _creditT[i].setFont(*_font);
        _creditT[i].setScale(1.5,1.5);
    }
    _creditT[0].setString("Ramiro Fernandez");
    _creditT[0].setPosition({100, 300});
    _creditT[1].setString("Araceli Fernandez");
    _creditT[1].setPosition({720, 300});
    _creditT[2].setString("Press Enter");
    _creditT[2].setPosition({520, 600});
    _creditT[2].setScale(1,1);
}


void Credit::initPlayers()
{
    int x = 300;
    for(int i=0; i<2; i++)
    {
        _player[i].setPosition({(x+600.f*i), 250.f});
        _player[i].setTextureRect( {0,0,48,48} );
    }
}
void Credit::initAnimation()
{
    _animation =  new Animation[2];
    if(_animation == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en Animation, en Credits"<<std::endl;
        exit(-1);
    }
    _animation[0] = Animation(48,48,"CHARACTER_SPRITES/Red/Red_Run.png", 5);
    _animation[0].applyToSprite(_player[0]);
    _animation[1] = Animation(48,48,"CHARACTER_SPRITES/Green/Green_Run.png", 5);
    _animation[1].applyToSprite(_player[1]);

}


bool Credit::volverMenu()
{
    return _volver;
}

void Credit::cmd()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        _time++;
    }
}

void Credit::update()
{
    float dt = 1.3f;
     _animation[0].update(dt);
     _animation[0].applyToSprite(_player[0]);
     _animation[1].update(dt);
     _animation[1].applyToSprite(_player[1]);

     if(_time >= 10 ) _volver = true;

}

void Credit::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    for(int i=0; i<3; i++) target.draw( _creditT[i], states);
    for(int i=0; i<2; i++) target.draw( _player[i], states);
}
