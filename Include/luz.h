#ifndef LUZ_H
#define LUZ_H

#include "Include/malla.h"
#include "Include/tuplasg.h"

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
    void setPos(float inc_X, float inc_Y, float inc_Z);
    Tupla4f getPos();
};

#endif // LUZ_H
