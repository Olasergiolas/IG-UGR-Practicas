#ifndef LUZDIRECCIONAL_H
#define LUZDIRECCIONAL_H

#include "luz.h"
#include "tuplasg.h"


class LuzDireccional : public Luz
{
public:
    LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
                   Tupla4f colorDifuso);
};

#endif // LUZDIRECCIONAL_H
