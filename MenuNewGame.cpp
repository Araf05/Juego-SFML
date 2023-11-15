#include "MenuNewGame.h"

MenuNewGame::MenuNewGame()
{
    initBackground();
    initFont();
    initText();

}

MenuNewGame::~MenuNewGame()
{
    delete [] _font;
}

void MenuNewGame::initText()
{
    _ingresar.setFont(*_font);
    _ingresar.setString("INGRESE SU NOMBRE: ");
    _ingresar.setPosition({460, 300});
}

void MenuNewGame::initBackground()
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

void MenuNewGame::initFont()
{
    _font = new sf::Font;
    if(_font == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en Fon, Menu New Game"<<std::endl;
    }
    if(!_font->loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Menu"<<std::endl;
        exit(-1);
    }
}



void MenuNewGame::cmd()
{
    sf::Text *auxName = new sf::Text;
    if(auxName == nullptr)
    {
        std::cout<<"Error en asignacion de memoria de aux name en Menu New Game"<<std::endl;
        exit(-1);
    }



}
void MenuNewGame::update()
{

}
void MenuNewGame::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    target.draw(_ingresar, states);
}
