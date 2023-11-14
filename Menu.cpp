#include "Menu.h"

Menu::Menu(const float& width, const float& height, const int& hayArchivo)
{
    initFont();
    initBackground();
    initOps(width, height, hayArchivo);

    _bak.setTexture(_background);
    _bak.setScale(1.25,1.15);
    _bak.setPosition({0,-300});

    _blackRec.setFillColor(sf::Color(0,0,25,180));
    _blackRec.setSize({width,height});
    _blackRec.setPosition({0,0});

    _hayArchivo = hayArchivo;
    _selectOps = 0;

}

Menu::~Menu()
{
    delete [] _options;
}

void Menu::initFont()
{
    if(!_font.loadFromFile("Fonts/Roboto-Black.ttf"))
    {
        std::cout<<"Error al cargar fuente en Menu"<<std::endl;
        exit(-1);
    }
}

void Menu::initBackground()
{
    if(!_background.loadFromFile("Background/bakMenu.jpeg"))
    {
        std::cout<<"Error al cargar png en Menu"<<std::endl;
        exit(-1);
    }
}

void Menu::initOps(const float& width, const float& height, const int& hayArchivo)
{
    if(!hayArchivo) _cantOps = 3;
    else _cantOps = 5;

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
        _options[i].setPosition({60, ((height/2)/(_cantOps + 1) *(i+1)) + (height/4) });
    }

    _options[0].setString("New Game");
    _options[0].setFillColor(sf::Color(215, 0, 12, 255));

    _options[_cantOps - 2].setString("Credits");
    _options[_cantOps -1].setString("Quit");

    if(hayArchivo)
    {
        _options[1].setString("Continue");
        _options[2].setString("Score");
    }


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

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        {
            _estado = ESTADOS_MENU::DOWN;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
            _estado = ESTADOS_MENU::UP;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) )
        {
            _estado = ESTADOS_MENU::ENTER;
        }
        else _estado = ESTADOS_MENU::IDLE;


}

void Menu::update(int& ops)
{
    _time++;

    if( (_time >= _holdTime) || (_estado == ESTADOS_MENU::ENTER) )
    {
        switch(_estado)
        {
            case ESTADOS_MENU::IDLE:

            break;
            case ESTADOS_MENU::DOWN:
                moveDown();
            break;
            case ESTADOS_MENU::UP:
                moveUp();
            break;
            case ESTADOS_MENU::ENTER:
                ops = _selectOps;
            break;
            default:
                _estado = ESTADOS_MENU::IDLE;
            break;

        }
        _time = 0;
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
