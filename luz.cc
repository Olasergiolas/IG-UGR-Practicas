#include "Include/luz.h"

void Luz::activar(){
    glLightfv(id, GL_POSITION, posicion);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_AMBIENT, colorAmbiente);
}

void Luz::setPos(float inc_X, float inc_Y, float inc_Z){
    posicion(X) += inc_X;
    posicion(Y) += inc_Y;
    posicion(Z) += inc_Z;
}

Tupla4f Luz::getPos(){
    return posicion;
}
