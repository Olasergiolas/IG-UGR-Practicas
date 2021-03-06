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
    bool examinando;
public:
    Camara(unsigned tipo, Tupla3f eye, Tupla3f at, Tupla3f up, unsigned height,
           unsigned width, int near, int far);
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);
    void girar(float x, float y);
    void avance_retroceso(float value);
    void desplazamiento_lateral(float value);
    void zoom(float factor);
    void setObserver();
    void setProyeccion();
    void setAt(Tupla3f newAt){at = newAt;}
    Tupla3f getEye(){return eye;}
    Tupla3f getAt(){return at;}
    void setAspect(float height, float width);
    bool getExaminando(){return examinando;}
    void setExaminando(bool estado){examinando = estado;}
};

#endif // CAMARA_H
