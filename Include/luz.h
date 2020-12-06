#ifndef LUZ_H
#define LUZ_H

#include "malla.h"
#include "tuplasg.h"

class Luz
{
protected:
    GLenum id;
    Tupla4f posicion;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

public:
    void activar();
};

#endif // LUZ_H
