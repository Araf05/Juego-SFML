#include "GameOver.h"

GameOver::GameOver()
{
    initBackground();
    initFont();
    initText();
    _selectOps = 0;
    _opsContinue = false;
    _time = 0;
}

GameOver::~GameOver()
{
    delete [] _font;
    delete [] _options;
}

void GameOver::initBackground()
{
    if(!_background.loadFromFile("Extras/gameover.png"))
    {
        std::cout<<"Error al cargar png en Game over"<<std::endl;
        exit(-1);
    }
    _bak.setTexture(_background);
    _bak.setScale(0.7,0.7);
    _bak.setPosition({410,10});

    _blackRec.setFillColor(sf::Color(0,0,25,180));
    _blackRec.setSize({1280,800});
    _blackRec.setPosition({0,0});
}

void GameOver::initFont()
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

void GameOver::initText()
{
    _continue.setFont(*_font);
    _continue.setString("CONTINUE?");
    _continue.setCharacterSize(40);
    _continue.setPosition({510, 500});
    _continue.setFillColor(sf::Color::White);

    _options = new sf::Text[2];
    if(_options == nullptr)
    {
        std::cout<<"Error de asignacion de memoria, opciones del Game Over"<<std::endl;
        exit(-1);
    }

    _options[0].setFont(*_font);
    _options[0].setString("yes");
    _options[0].setPosition({540, 560});
    _options[0].setFillColor(sf::Color(215, 0, 12, 255));

    _options[1].setFont(*_font);
    _options[1].setString("no");
    _options[1].setPosition({660, 560});
    _options[1].setFillColor(sf::Color::White);
}

int GameOver::opsContinue()
{
    return _selectOps;
}

bool GameOver::pressEnter()
{
    return _opsContinue;
}

void GameOver::moveLeft()
{
    if(_selectOps == 1)
    {
        _options[_selectOps].setFillColor(sf::Color::White);
        _selectOps--;
        _options[_selectOps].setFillColor(sf::Color(215, 0, 12, 255));
    }
}

void GameOver::moveRight()
{
    if(_selectOps == 0)
    {
        _options[_selectOps].setFillColor(sf::Color::White);
        _selectOps++;
        _options[_selectOps].setFillColor(sf::Color(215, 0, 12, 255));
    }
}

void GameOver::cmd()
{
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
    {
        _estado = ESTADOS_GAMEOVER::LEFT;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
    {
        _estado = ESTADOS_GAMEOVER::RIGHT;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) )
    {
        _estado = ESTADOS_GAMEOVER::ENTER;
    }
    else _estado = ESTADOS_GAMEOVER::IDLE;
}


void GameOver::update()
{
    _time++;

    if( (_time >= _holdTime) || (_estado == ESTADOS_GAMEOVER::ENTER) )
    {
        switch(_estado)
        {
            case ESTADOS_GAMEOVER::IDLE:

            break;
            case ESTADOS_GAMEOVER::LEFT:
                moveLeft();
            break;
            case ESTADOS_GAMEOVER::RIGHT:
                moveRight();
            break;
            case ESTADOS_GAMEOVER::ENTER:
                _opsContinue = true;
            break;
            default:
                _estado = ESTADOS_GAMEOVER::IDLE;
            break;

        }
        _time = 0;
    }

}


void GameOver::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(_bak, states);
    target.draw(_blackRec, states);
    target.draw(_continue, states);
    for(int i=0; i<2; i++) target.draw(_options[i], states);
}
