#ifndef CAMARA_H
#define CAMARA_H

#include "Include/aux.h"

class Camara
{
private:
    Tupla3f eye, at, up;
    Tupla3f z_axis, x_axis, y_axis;

    unsigned tipo;
    float left, right, top, bottom, near, far, aspect, fovy;
public:
    Camara(unsigned tipo, Tupla3f eye, Tupla3f at, Tupla3f up, unsigned height,
           unsigned width);
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    /*void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);*/
    void mover(float x, float y, float z);
    void zoom(float factor);
    void setObserver();
    void setProyeccion();
};

#endif // CAMARA_H
