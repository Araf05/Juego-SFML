#include "Partida.h"

Partida::Partida(std::string nombre, const int& puntos)
{
    setName(nombre);
    setPoints(puntos);
    setEstado(true);
}

Partida::~Partida()
{
    //dtor
}

void Partida::setName(std::string nombre)
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

std::string Partida::getName() const
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
