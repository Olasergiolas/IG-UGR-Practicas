#include "Include/luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorDifuso,
                             Tupla4f colorEspecular)
{
    Tupla4f aux(posicion(X), posicion(Y), posicion(Z), 1);
    this->posicion = aux;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    id = idLuzOpenGL;
}
