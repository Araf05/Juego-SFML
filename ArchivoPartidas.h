#ifndef ARCHIVOPARTIDAS_H
#define ARCHIVOPARTIDAS_H
#include <cstring>
#include "Partida.h"

class ArchivoPartidas
{
    public:
        ArchivoPartidas(const char* fileName);
        virtual ~ArchivoPartidas();

        Partida leerRegistro(int pos);
        int contarRegistros();
        bool grabarRegistro(Partida reg);

    private:
        char _fileName[30];
};

#endif // ARCHIVOPARTIDAS_H
