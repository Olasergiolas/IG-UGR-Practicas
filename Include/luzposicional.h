#ifndef LUZPOSICIONAL_H
#define LUZPOSICIONAL_H

#include "Include/luz.h"
#include "Include/tuplasg.h"


class LuzPosicional : public Luz
{
public:
    LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorDifuso,
                   Tupla4f colorEspecular);
};

#endif // LUZPOSICIONAL_H
