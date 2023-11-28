#include "Partida.h"

Partida::~Partida()
{
    //dtor
}

void Partida::setName(std::string nombre)
{
    strcpy(_name, nombre.c_str());
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
    std::string nombre;
    nombre.append(_name);
    return nombre;
}

int Partida::getPoints()
{
    return _points;
}

bool Partida::getEstado()
{
    return _estado;
}
