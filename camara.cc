#include "Include/camara.h"

Camara::Camara(unsigned tipo, Tupla3f eye, Tupla3f at, Tupla3f up, unsigned heigth,
               unsigned width, int near, int far)
{
    this->tipo = tipo;
    this->eye = eye;
    this->at = at;
    this->up = up;

    setAspect(heigth, width);
    this->near = near;
    this->far = far;
    //fovy = 2*atan((width/2)/aspect) * (180/M_PI);

    z_axis = eye - at;
    z_axis = z_axis.normalized();

    x_axis = up.cross(z_axis);
    x_axis = x_axis.normalized();

    y_axis = z_axis.cross(x_axis);
}

void Camara::setAspect(float heigth, float width){
    aspect = width/heigth;
    top = (heigth/2);
    bottom = (-top);
    right = width/2;
    left = -right;
}

void Camara::rotarXExaminar(float angle){
    //Obtenemos el vector direccion que va del at hacia el eye
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    //Rotamos el vector
    direccion(Y) = direccionAux(Y) * cos(angle) - direccionAux(Z) * sin(angle);
    direccion(Z) = direccionAux(Y) * sin(angle) + direccionAux(Z) * cos(angle);

    //Actualizamos eye
    eye = direccion + at;
}

void Camara::rotarYExaminar(float angle){
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    direccion(X) = direccionAux(X) * cos(angle) + direccionAux(Z) * sin(angle);
    direccion(Z) = direccionAux(X) * -sin(angle) + direccionAux(Z) * cos(angle);

    eye = direccion + at;
}

void Camara::rotarZExaminar(float angle){
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    direccion(X) = direccionAux(X) * cos(angle) - direccionAux(Z) * sin(angle);
    direccion(Y) = direccionAux(X) * sin(angle) + direccionAux(Z) * cos(angle);

    eye = direccion + at;
}

void Camara::rotarXFirstPerson(float angle){
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    direccion(Y) = direccionAux(Y) * cos(angle) - direccionAux(Z) * sin(angle);
    direccion(Z) = direccionAux(Y) * sin(angle) + direccionAux(Z) * cos(angle);

    at = direccion + eye;
}

void Camara::rotarYFirstPerson(float angle){
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    direccion(X) = direccionAux(X) * cos(angle) + direccionAux(Z) * sin(angle);
    direccion(Z) = direccionAux(X) * -sin(angle) + direccionAux(Z) * cos(angle);

    at = direccion + eye;
}

void Camara::rotarZFirstPerson(float angle){
    Tupla3f direccion = eye - at;
    Tupla3f direccionAux = direccion;

    direccion(X) = direccionAux(X) * cos(angle) - direccionAux(Z) * sin(angle);
    direccion(Y) = direccionAux(X) * sin(angle) + direccionAux(Z) * cos(angle);

    at = direccion + eye;
}

void Camara::girar(float x, float y){
    rotarXFirstPerson(-y*0.25*M_PI/180.0);
    rotarYFirstPerson(-x*0.25*M_PI/180.0);
}

void Camara::setObserver(){
    gluLookAt(eye(X), eye(Y), eye(Z),
              at(X), at(Y), at(Z),
              up(X), up(Y), up(Z));
}

void Camara::setProyeccion(){
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if (tipo == 0)
        glFrustum(left * aspect, right * aspect, bottom * aspect, top * aspect, near, far);

    else if (tipo == 1)
        glOrtho(left * aspect, right * aspect, bottom * aspect , top * aspect , near, far);
}

void Camara::mover(float x, float y, float z){
    eye(X) = x; eye(Y) = y; eye(Z) = z;
}

void Camara::zoom(float factor){
    right *= factor;
    left *= factor;
    top *= factor;
    bottom *= factor;

    setProyeccion();
}
