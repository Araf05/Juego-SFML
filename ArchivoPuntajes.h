#ifndef ARCHIVOPUNTAJES_H
#define ARCHIVOPUNTAJES_H
#include <cstring>
#include "Puntaje.h"

class ArchivoPuntajes
{
    public:
        ArchivoPuntajes(const char* fileName);
        virtual ~ArchivoPuntajes();

        Puntaje leerRegistro(int pos);
        int contarRegistros();
        bool grabarRegistro(Puntaje reg);
        bool modificar(const int&pos, const Puntaje& reg);
        void cargarVector(Puntaje *vec, const int& cantReg);
        bool ordenarRegistro();

    private:
        char _fileName[30];
};

#endif // ARCHIVOPUNTAJES_H
