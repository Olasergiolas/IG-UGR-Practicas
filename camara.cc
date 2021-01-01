#include "Include/camara.h"

Camara::Camara(unsigned tipo, Tupla3f eye, Tupla3f at, Tupla3f up, unsigned heigth,
               unsigned width)
{
    this->tipo = tipo;
    this->eye = eye;
    this->at = at;
    this->up = up;

    aspect = width/heigth;
    top = heigth/2;
    bottom = -top;
    right = width/2;
    left = -right;
    near = 50.0f;
    far = 2000.0f;
    fovy = 2*atan((width/2)/aspect) * (180/M_PI);

    z_axis = eye - at;
    z_axis = z_axis.normalized();

    x_axis = up.cross(z_axis);
    x_axis = x_axis.normalized();

    y_axis = z_axis.cross(x_axis);
}

void Camara::rotarXExaminar(float angle){
    Tupla3f eyeAux = eye;
    eye(Y) = eyeAux(Y) * cos(angle) - eyeAux(Z) * sin(angle);
    eye(Z) = eyeAux(Y) * sin(angle) + eyeAux(Z) * cos(angle);
}

void Camara::rotarYExaminar(float angle){
    Tupla3f eyeAux = eye;
    eye(X) = eyeAux(X) * cos(angle) + eyeAux(Z) * sin(angle);
    eye(Z) = eyeAux(X) * -sin(angle) + eyeAux(Z) * cos(angle);
}

void Camara::rotarZExaminar(float angle){
    Tupla3f eyeAux = eye;
    eye(X) = eyeAux(X) * cos(angle) - eyeAux(Z) * sin(angle);
    eye(Y) = eyeAux(X) * sin(angle) + eyeAux(Z) * cos(angle);
}


void Camara::setObserver(){
    gluLookAt(eye(X), eye(Y), eye(Z),
              at(X), at(Y), at(Z),
              up(X), up(Y), up(Z));
}

void Camara::setProyeccion(){
    if (tipo == 0)
        gluPerspective(fovy, aspect, near, far);

    else if (tipo == 1)
        glOrtho(left, right, bottom, top, near, far);
}

void Camara::mover(float x, float y, float z){
    eye(X) = x; eye(Y) = y; eye(Z) = z;
}
