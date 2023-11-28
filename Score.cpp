#include "Score.h"

Score::Score()
{
    initCantReg();
    std::cout<<"Score registros leidos: "<< _cantReg<<std::endl;

    initVecPuntajes();
    initBackground();
    initFont();
    initTitulo();

    _filas = _cantReg;
    _cols = 3;
    initScore();
    updateScore();

    _volver = false;
    _time=0;
}

Score::~Score()
{
    delete [] _font;
    delete [] _titulo;
    delete [] _score;
    delete [] _vecPuntajes;
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
    _titulo[1].setPosition({_colum1, _scoreFila});
    _titulo[2].setString("NOMBRE");
    _titulo[2].setPosition({_colum2, _scoreFila});
    _titulo[3].setString("PUNTAJE");
    _titulo[3].setPosition({_colum3, _scoreFila});
    _titulo[4].setString("Press Enter");
    _titulo[4].setPosition({520, 600});

}

void Score::initCantReg()
{
    ArchivoPuntajes file("puntajes.dat");

    _cantReg = file.contarRegistros();
}


void Score::initVecPuntajes()
{
    _vecPuntajes = new Puntaje[_cantReg];
    if(_vecPuntajes == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en vector de Puntajes, Score"<<std::endl;
        exit(-1);
    }
    ArchivoPuntajes file("puntajes.dat");

    for(int i=0; i<_cantReg; i++)
    {
        _vecPuntajes[i] = file.leerRegistro(i);
        _vecPuntajes[i].Mostrar();
    }
}



void Score::initScore()
{
    _score = new sf::Text*[_filas];
    if(_score == nullptr)
    {
        std::cout<<"Error de aisgnacion de memoria, matriz de score (filas)"<<std::endl;
        exit(-1);
    }
    for(int i=0; i<_filas; i++)
    {
        _score[i] = new sf::Text[_cols];
        if(_score[i] == nullptr)
        {
            std::cout<<"Error de aisgnacion de memoria, matriz de score (cols)"<<std::endl;
            exit(-1);
        }
    }

    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            _score[i][j].setFont(*_font);
        }
    }

}

void Score::updateScore()
{
    int j;
    _scoreFila+=60;
    for(int i=0; i<_filas; i++)
    {
        j=0;
        _score[i][j].setString(std::to_string(i+1));
        _score[i][j].setPosition({_colum1,_scoreFila+(60*i)});

        j=1;
        _score[i][j].setString(_vecPuntajes[i].getName());
        _score[i][j].setPosition({_colum2, _scoreFila+(60*i)});

        j=2;
        _score[i][j].setString(std::to_string(_vecPuntajes[i].getPoints()));
        _score[i][j].setPosition({_colum3, _scoreFila+(60*i)});
    }
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

    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
           target.draw( _score[i][j], states);
        }
    }

}
