#include "Menu.h"

Menu::Menu(const float& width, const float& height)
{
    _hayArchivo = buscarScore();
    initFont();
    initBackground();
    initOps(width, height);

    _blackRec.setFillColor(sf::Color(0,0,25,180));
    _blackRec.setSize({width,height});
    _blackRec.setPosition({0,0});
    _selectOps = 0;

}

Menu::~Menu()
{
    delete [] _options;
}

bool Menu::buscarScore()
{
    ArchivoPuntajes file("puntajes.dat");
    Puntaje reg;
    int cantReg = file.contarRegistros();
    if(cantReg < 0)
    {
        return false;
    }
    return true;
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
    _bak.setTexture(_background);
    _bak.setScale(1.25,1.15);
    _bak.setPosition({0,-300});
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
        _options[i].setPosition({60, ((height/2)/(_cantOps + 1) *(i+1)) + (height/4) });
    }

    _options[0].setString("New Game");
    _options[0].setFillColor(sf::Color(215, 0, 12, 255));

    _options[1].setString("Score");
    _options[2].setString("Credits");
    _options[3].setString("Quit");

    if(!_hayArchivo)
    {
        _options[1].setFillColor(sf::Color(255, 255, 255, 60));
    }

}


void Menu::moveUp()
{
    if((_selectOps - 1) >=0)
    {
        _options[_selectOps].setFillColor(sf::Color::White);

        if(!_hayArchivo && _selectOps == 2 )
        {
            _selectOps = 0;
        } else _selectOps--;

        _options[_selectOps].setFillColor(sf::Color(215, 0, 12, 255));
    }
}

void Menu::moveDown()
{
    if((_selectOps + 1) < _cantOps)
    {
        _options[_selectOps].setFillColor(sf::Color::White);
        if(!_hayArchivo && _selectOps == 0 )
        {
            _selectOps = 2;
        } else _selectOps++;

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
