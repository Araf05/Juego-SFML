#ifndef PARTIDA_H
#define PARTIDA_H
#include <SFML/Graphics.hpp>

class Partida
{
    public:
        Partida(){};
        Partida(const sf::Text& nombre , const int& puntos);
        virtual ~Partida();

        void setName(const sf::Text& nombre);
        void setPoints(const int& puntos);
        void setEstado(bool estado);

        sf::Text getName();
        int getPoints();
        bool getEstado();

    private:
        sf::Text _name;
        int _points;
        bool _estado;
};

#endif // PARTIDA_H
