#ifndef PUNTAJE_H
#define PUNTAJE_H
#include <iostream>
#include <cstring>

class Puntaje
{
    public:
        Puntaje(){};
        virtual ~Puntaje();
        void setName(std::string name);
        void setPoints(const int& puntos);
        void setEstado(bool estado);

        std::string getName() const;
        int getPoints();
        bool getEstado();

    private:
        char _name[20];
        int _points;
        bool _estado = true;
};

#endif // PUNTAJE_H
