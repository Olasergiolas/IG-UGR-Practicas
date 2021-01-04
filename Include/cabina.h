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
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
              Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));
    void setAlpha(float value);
    void setMaterial(Material m);
    void setColor(Tupla3f color);
};

#endif // CABINA_H
