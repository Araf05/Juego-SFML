#include "Score.h"

Score::Score(const std::string& nombre, const int& puntos)
{
//    initCantReg();
//    initVecPuntajes(nombre, puntos);
    initBackground();
    initFont();
    initTitulo();

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


void Score::initVecPuntajes(const std::string& nombre, const int& puntos)
{
    initCantReg();
    if(_cantReg < 1) _cantReg = 1;
    else if(_cantReg<6) _cantReg++;
    std::cout<< _cantReg<<std::endl;
    _vecPuntajes = new Puntaje[_cantReg];
    if(_vecPuntajes == nullptr)
    {
        std::cout<<"Error de asignacion de memoria en vector de Puntajes, Score"<<std::endl;
        exit(-1);
    }
    ArchivoPuntajes file("puntajes.dat");
    Puntaje reg;

    if(_cantReg > 1)
    {
        for(int i=0; i<_cantReg; i++)
        {
            reg = file.leerRegistro(i);
            _vecPuntajes[i].setName(reg.getName());
            _vecPuntajes[i].setPoints(reg.getPoints());
            _vecPuntajes[i].setEstado(reg.getEstado());
        }
    }
    _vecPuntajes[_cantReg-1].setName(nombre);
    _vecPuntajes[_cantReg-1].setPoints(puntos);
    _vecPuntajes[_cantReg-1].setEstado(true);

   if(_cantReg>1) ordenarPuntajes();

    if(_cantReg == 6) _vecPuntajes[_cantReg-1].setEstado(false);

    if(_cantReg == 1) file.grabarRegistro(_vecPuntajes[0]);
    else updateFile();
}

void Score::ordenarPuntajes()
{
    int posmax;
    Puntaje aux;
    for(int i=0; i<_cantReg-1; i++)
    {
        posmax = i;
        for(int j=i+1; j<_cantReg; j++)
        {
            if(_vecPuntajes[j].getPoints() > _vecPuntajes[posmax].getPoints())
            {
                posmax = j;
                aux = _vecPuntajes[i];
                _vecPuntajes[i] = _vecPuntajes[j];
                _vecPuntajes[j] = aux;
            }
        }
    }
}

bool Score::updateFile()
{
    ArchivoPuntajes file("puntajes.dat");

    for(int i=0; i<_cantReg; i++)
    {
        file.modificar(i, _vecPuntajes[i]);
    }
    return true;
}

void Score::initScore()
{
    _score = new sf::Text**[_filas];
    if(_score == nullptr)
    {
        std::cout<<"Error de aisgnacion de memoria, matriz de Tiles (cols)"<<std::endl;
        exit(-1);
    }
    for(int i=0; i<_filas; i++)
    {
        _score[i] = new sf::Text*[_cols]{};
        if(_score[i] == nullptr)
        {
            std::cout<<"Error de aisgnacion de memoria, matriz de Tiles (filas)"<<std::endl;
            exit(-1);
        }
    }

    for(int i=0; i<_filas; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            _score[i][j]->setFont(*_font);
        }
    }
}

void Score::updateScore()
{
    std::string aux;
    int j;
    for(int i=0; i<_filas; i++)
    {
        j=0;
        aux = std::to_string(i+1);
        _score[i][j]->setString(aux);
        _score[i][j]->setPosition({_colum1,_scoreFila+(60*j)});

        j++;
        aux = _vecPuntajes[i].getName();
        _score[i][j]->setString(aux);
        _score[i][j]->setPosition({_colum2, _scoreFila+(60*j)});

        j++;
        aux = std::to_string(_vecPuntajes[i].getPoints());
        _score[i][j]->setString(aux);
        _score[i][j]->setPosition({_colum2, _scoreFila+(60*j)});
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
           target.draw( *_score[i][j], states);
        }
    }

}
