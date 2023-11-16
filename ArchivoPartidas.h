#ifndef ARCHIVOPARTIDAS_H_INCLUDED
#define ARCHIVOPARTIDAS_H_INCLUDED

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


#endif // ARCHIVOPARTIDAS_H_INCLUDED
