#include "ArchivoPartidas.h"

ArchivoPartidas::ArchivoPartidas(const char* fileName)
{
    strcpy(_fileName, fileName);
}

ArchivoPartidas::~ArchivoPartidas()
{
    //dtor
}


Partida ArchivoPartidas::leerRegistro(int pos){
    Partida reg;
    reg.setEstado(false);
    FILE *p=fopen(_fileName, "rb");
    if(p==NULL) return reg;

    fseek(p, sizeof reg*pos, 0);
    fread(&reg, sizeof(Partida), 1, p);
    fclose(p);
    return reg;
}

int ArchivoPartidas::contarRegistros(){
    FILE *p;
    p=fopen(_fileName, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Partida);
}

bool ArchivoPartidas::grabarRegistro(Partida reg){
    FILE *p;
    p=fopen(_fileName, "wb");
    if(p==NULL) return false;
    bool escribio=fwrite(&reg, sizeof reg,1, p);
    fclose(p);
    return escribio;
}

