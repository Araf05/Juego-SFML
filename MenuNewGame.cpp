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
        std::cout<<"Error de asignacion de memoria en Font, Menu New Game"<<std::endl;
        exit(-1);
    }
    if(!_font->loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Menu"<<std::endl;
        exit(-1);
    }
}



void MenuNewGame::cmd(const sf::Event& event)
{
    static sf::Uint32 prevChar = 0;
    if(event.type == sf::Event::TextEntered && event.text.unicode!= prevChar)
    {
        prevChar = event.text.unicode;
        switch (event.text.unicode)
        {
            case 13:
               // _estado = ESTADOS_NEWGAME::PRESIONA_ENTER;
                if(!nombre.empty())
                {
                    ingreso = true;
                }
            break;
            default: // Ha pulsado algo que no es enter
                if(event.text.unicode < 128)
                {
                    nombre += static_cast<char>(event.text.unicode);
                    _name->setString(nombre);
                }
            break;
        }
    }

}

std::string MenuNewGame::getNombre() const
{
    return nombre;
}

sf::Text MenuNewGame::getName()
{
    return *_name;
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
