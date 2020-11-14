#ifndef LUZPOSICIONAL_H
#define LUZPOSICIONAL_H

#include "luz.h"
#include "tuplasg.h"


class LuzPosicional : public Luz
{
public:
    LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
                   Tupla4f colorDifuso);

    LuzPosicional(const Tupla3f& posicion);
};

#endif // LUZPOSICIONAL_H
