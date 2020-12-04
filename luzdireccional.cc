#include "luzdireccional.h"
#include "math.h"

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorDifuso,
                               Tupla4f colorEspecular)
{
    alpha = direccion(0);
    beta = direccion(1);
    posicion = Tupla4f(0.0, 0.0, 1.0, 0.0);
    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    Tupla4f aux = posicion;
    alpha += incremento;
    
    aux(Z) = posicion(Z) * cos(incremento) - posicion(X) * sin(incremento);
    aux(X) = posicion(Z) * sin(incremento) + posicion(X) * cos(incremento);
    aux(Y) = posicion(Y);

    posicion = aux;
}

void LuzDireccional::variarAnguloBeta(float incremento){
    Tupla4f aux = posicion;
    beta += incremento;

    aux(Y) = posicion(Y) * cos(incremento) - posicion(Z) * sin(incremento);
    aux(Z) = posicion(Y) * sin(incremento) + posicion(Z) * cos(incremento);
    aux(X) = posicion(X);

    posicion = aux;
}
