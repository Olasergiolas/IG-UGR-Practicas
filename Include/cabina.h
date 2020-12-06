#ifndef CABINA_H
#define CABINA_H

#include "Include/esfera.h"
#include "Include/cilindro.h"

class Cabina
{
private:
    Cilindro *cabina = nullptr;
    Esfera *semiesfera = nullptr;
    float alpha;

public:
    Cabina();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado);
};

#endif // CABINA_H
