#ifndef PARTIDA_H
#define PARTIDA_H
#include <SFML/Graphics.hpp>

class Partida
{
    public:
        Partida(){};
        Partida(std::string nombre , const int& puntos);
        virtual ~Partida();

        void setName(std::string name);
        void setPoints(const int& puntos);
        void setEstado(bool estado);

        std::string getName() const;
        int getPoints();
        bool getEstado();

    private:
        std::string _name;
        int _points;
        bool _estado;
};

#endif // PARTIDA_H
