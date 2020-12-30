#ifndef FOCO_H
#define FOCO_H

#include "Include/cono.h"
#include "Include/esfera.h"

class Foco
{
private:
    Cono *cono = nullptr;
    Esfera *esfera = nullptr;

public:
    Foco();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado);
};

#endif // FOCO_H
