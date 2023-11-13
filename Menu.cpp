#include "Menu.h"

Menu::Menu(float width, float height)
{
    if(!_font.loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Menu"<<std::endl;
        exit(-1);
    }
    initOps(width, height);
    if(!_background.loadFromFile("Background/bakMenu.jpeg"))
    {
        std::cout<<"Error al cargar png en Menu"<<std::endl;
        exit(-1);
    }
    _bak.setTexture(_background);
    _bak.setScale(1.25,1.15);
    _bak.setPosition({0,-300});

    _blackRec.setFillColor(sf::Color(56,58,126,200));
    _blackRec.setSize({400,height});
    _blackRec.setPosition({0,0});

    _selectOps = 0;




}

Menu::~Menu()
{
    delete [] _options;
}

void Menu::initOps(const float& width, const float& height)
{
    _options = new sf::Text[_cantOps];
    if(_options == nullptr)
    {
        std::cout<<"Error de asignacion de memoria, opciones del Menu"<<std::endl;
        exit(-1);
    }

    for(int i=0; i<_cantOps; i++)
    {
        _options[i].setFont(_font);
        _options[i].setFillColor(sf::Color::White);
        _options[i].setPosition({60, (height/(_cantOps + 1) *(i+1))});
    }

    _options[0].setString("New Game");
    _options[0].setFillColor(sf::Color(215, 0, 12, 255));

    _options[1].setString("Continue");
    _options[2].setString("Score");
    _options[3].setString("Credits");
    _options[4].setString("Quit");
}


void Menu::moveUp()
{
    if((_selectOps - 1) >=0)
    {
        _options[_selectOps].setFillColor(sf::Color::White);
        _selectOps--;
        _options[_selectOps].setFillColor(sf::Color(215, 0, 12, 255));
    }
}

void Menu::moveDown()
{
    if((_selectOps + 1) < _cantOps)
    {
        _options[_selectOps].setFillColor(sf::Color::White);
        _selectOps++;
        _options[_selectOps].setFillColor(sf::Color(215, 0, 12, 255));
    }
}

void Menu::cmd()
{
    if(_estado == ESTADOS_MENU::IDLE)
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        {
            _estado = ESTADOS_MENU::DOWN;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
            _estado = ESTADOS_MENU::UP;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) )
        {
            _estado = ESTADOS_MENU::ENTER;
            std::cout<<"enter"<<std::endl;
        }
    }
}

void Menu::update()
{
    switch(_estado)
    {
        case ESTADOS_MENU::IDLE:

        break;
        case ESTADOS_MENU::DOWN:
            moveDown();
            _estado = ESTADOS_MENU::IDLE;
        break;
        case ESTADOS_MENU::UP:
            moveUp();
            _estado = ESTADOS_MENU::IDLE;
        break;
        case ESTADOS_MENU::ENTER:
        break;
    }
}

void Menu::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    for(int i=0; i<_cantOps; i++)
    {
        target.draw(_options[i], states);
    }
}
