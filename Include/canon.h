#ifndef CANON_H
#define CANON_H

#include "Include/cilindro.h"
#include "Include/cono.h"

class Canon{
private:
    Cilindro *cilindro = nullptr;
    Cono *base = nullptr;

public:
    Canon();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
              Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));
};

#endif // CANON_H
