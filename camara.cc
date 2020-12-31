#include "Include/camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up)
{
    this->eye = eye;
    this->at = at;
    this->up = up;

    direccion = at - eye;   //o es eye - at?

}

void Camara::setObserver(){
    gluLookAt(eye(X), eye(Y), eye(Z),
              at(X), at(Y), at(Z),
              up(X), up(Y), up(Z));
}

void Camara::setProyeccion(){
    if (tipo == 0)
        gluPerspective(fov, aspect, near, far);

    else if (tipo == 1)
        glOrtho(left, right, bottom, top, near, far);
}

void Camara::mover(float x, float y, float z){
    eye(X) = x; eye(Y) = y; eye(Z) = z;
}
