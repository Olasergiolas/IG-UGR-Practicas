#ifndef LUZDIRECCIONAL_H
#define LUZDIRECCIONAL_H

#include "luz.h"
#include "tuplasg.h"


class LuzDireccional : public Luz
{
protected:
    float alpha;
    float beta;

public:
    LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
                   Tupla4f colorDifuso);

    LuzDireccional(const Tupla2f& orientacion);

    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
    float getAlpha() {return alpha;};
    float getBeta() {return beta;};
};

#endif // LUZDIRECCIONAL_H
