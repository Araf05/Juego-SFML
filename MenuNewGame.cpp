#include "MenuNewGame.h"

MenuNewGame::MenuNewGame()
{
    initBackground();
    initFont();
    initText();
    initName();

}

MenuNewGame::~MenuNewGame()
{
    delete [] _font;
}

void MenuNewGame::initName()
{
    _name = new sf::Text;
    if(_name==nullptr)
    {
        std::cout<<"Error al asignar memoria al name en Menu New Game"<<std::endl;
        exit(-1);
    }

    _name->setPosition({460, 340});
    _name->setFont(*_font);

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



void MenuNewGame::cmd(const sf::Event& event)
{
    if(event.type == sf::Event::TextEntered)
    {
        switch (event.text.unicode)
        {
            case 13:
                _estado = ESTADOS_NEWGAME::PRESIONA_ENTER;
            break;
            default: // Ha pulsado algo que no es enter
                nombre.push_back(event.text.unicode);
                break;
        }
    }

     std::cout<< nombre<<std::endl;
    _name->setString(nombre);

}
void MenuNewGame::update()
{


}
void MenuNewGame::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    target.draw(_ingresar, states);
    target.draw(*_name, states);
}
