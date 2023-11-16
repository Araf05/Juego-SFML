#include "Partida.h"

Partida::Partida(const sf::Text& nombre, const int& puntos)
{
    setName(nombre);
    setPoints(puntos);
    setEstado(true);
}

Partida::~Partida()
{
    //dtor
}

void Partida::setName(const sf::Text& nombre)
{
    _name = nombre;
}
void Partida::setPoints(const int& puntos)
{
    _points = puntos;
}

void Partida::setEstado(bool estado)
{
    _estado = estado;
}

sf::Text Partida::getName()
{
    return _name;
}

int Partida::getPoints()
{
    return _points;
}

bool Partida::getEstado()
{
    return _estado;
}
