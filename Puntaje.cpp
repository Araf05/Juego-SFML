#include "Puntaje.h"

Puntaje::~Puntaje()
{
    //dtor
}

void Puntaje::setName(std::string nombre)
{
    strcpy(_name, nombre.c_str());
}

void Puntaje::setPoints(const int& puntos)
{
    _points = puntos;
}


void Puntaje::setEstado(bool estado)
{
    _estado = estado;
}

std::string Puntaje::getName() const
{
    std::string nombre;
    nombre.append(_name);
    return nombre;
}

int Puntaje::getPoints()
{
    return _points;
}

bool Puntaje::getEstado()
{
    return _estado;
}
