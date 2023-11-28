#include "ArchivoPuntajes.h"

ArchivoPuntajes::ArchivoPuntajes(const char* fileName)
{
    strcpy(_fileName, fileName);
}

ArchivoPuntajes::~ArchivoPuntajes()
{
    //dtor
}


Puntaje ArchivoPuntajes::leerRegistro(int pos){
    Puntaje reg;
    reg.setEstado(false);
    FILE *p=fopen(_fileName, "rb");
    if(p==NULL) return reg;

    fseek(p, sizeof reg*pos, 0);
    fread(&reg, sizeof(Puntaje), 1, p);
    fclose(p);
    return reg;
}

int ArchivoPuntajes::contarRegistros(){
    FILE *p;
    p=fopen(_fileName, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Puntaje);
}

bool ArchivoPuntajes::grabarRegistro(Puntaje reg){
    FILE *p;
    p=fopen(_fileName, "ab");
    if(p==NULL) return false;
    bool escribio=fwrite(&reg, sizeof reg,1, p);
    fclose(p);
    return escribio;
}

bool ArchivoPuntajes::modificar(const int&pos, const Puntaje& reg)
{
    FILE* p= fopen( _fileName, "rb+");
    if(p == nullptr) return false;

    fseek(p, sizeof(Puntaje)*pos, SEEK_SET);

    if (fwrite(&reg, sizeof(Puntaje), 1, p) == 1 )
    {
        fclose(p);
        return true;
    }
    std::cout<< "Error, el registro NO pudo ser modificado..."<< std::endl;
    fclose(p);
    return false;
}

void ArchivoPuntajes::cargarVector(Puntaje *vec, const int& cantReg)
{
    for(int i=0; i<cantReg; i++)
    {
        *vec= leerRegistro(i);
    }
}

bool ArchivoPuntajes::ordenarRegistro()
{
    int posmax, cantReg = contarRegistros();
    Puntaje aux, *v;

    v = new Puntaje[cantReg];
    if(v == nullptr)
    {
        std::cout<<"Error al asignar memoria al vector en Archivo Puntajes"<<std::endl;
        delete [] v;
        return false;
    }
    cargarVector(v, cantReg);

    for(int i=0; i<cantReg-1; i++)
    {
        posmax = i;
        for(int j=i+1; j<cantReg; j++)
        {
            if(v[j].getPoints() > v[posmax].getPoints())
            {
                posmax = j;
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }

    for(int i=0; i<cantReg; i++)
    {
        modificar(i,v[i]);
    }
    return true;
}

