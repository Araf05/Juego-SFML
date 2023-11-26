#include "Score.h"

Score::Score()
{
    initBackground();
    initFont();
    initTitulo();
    //initScore();

    _volver = false;
    _time=0;
}

Score::~Score()
{
    delete [] _font;
    delete [] _titulo;
    delete [] _score;
}

void Score::initBackground()
{
    if(!_background.loadFromFile("Background/bakMenu.jpeg"))
    {
        std::cout<<"Error al cargar png en Score"<<std::endl;
        exit(-1);
    }
    _bak.setTexture(_background);
    _bak.setScale(1.25,1.15);
    _bak.setPosition({0,-300});

    _blackRec.setFillColor(sf::Color(0,0,25,180));
    _blackRec.setSize({1280,800});
    _blackRec.setPosition({0,0});
}

void Score::initFont()
{
    _font = new sf::Font;
    if(_font == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en Font, Score"<<std::endl;
        exit(-1);
    }
    if(!_font->loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Score"<<std::endl;
        exit(-1);
    }
}

void Score::initTitulo()
{
    _titulo = new sf::Text[5];
    for(int i=0; i<5; i++ )
    {
        _titulo[i].setFont(*_font);
    }
    _titulo[0].setString("HIGH-SCORE");
    _titulo[0].setPosition({550, 50});
    _titulo[1].setString("PUESTO");
    _titulo[1].setPosition({200, 200});
    _titulo[2].setString("NOMBRE");
    _titulo[2].setPosition({450, 200});
    _titulo[3].setString("PUNTAJE");
    _titulo[3].setPosition({820, 200});
    _titulo[4].setString("Press Enter");
    _titulo[4].setPosition({520, 600});

}


bool Score::volverMenu()
{
    return _volver;
}

void Score::cmd()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        _time++;
    }
}

void Score::update()
{
     if(_time >= 10 ) _volver = true;
}

void Score::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    for(int i=0; i<5; i++) target.draw( _titulo[i], states);
//    for(int i=0; i<2; i++) target.draw( _player[i], states);
}
