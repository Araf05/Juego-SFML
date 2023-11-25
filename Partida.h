#ifndef PARTIDA_H
#define PARTIDA_H
#include <cstring>
#include <SFML/Graphics.hpp>

class Partida
{
    public:
        Partida(){};
        virtual ~Partida();

        void setName(std::string name);
        void setPoints(const int& puntos);
        void setEstado(bool estado);

        std::string getName() const;
        int getPoints();
        bool getEstado();

    private:
        char _name[20];
        int _points;
//        int _level;
//        int _gold;
//        int _gun;
        bool _estado = true;
};

#endif // PARTIDA_H
