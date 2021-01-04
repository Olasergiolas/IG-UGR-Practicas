#ifndef CUERPO_H
#define CUERPO_H

#include "Include/tetraedro.h"
#include "Include/cabina.h"
#include "Include/foco.h"

class Cuerpo
{
private:
    Tetraedro *morro = nullptr;
    Foco *foco = nullptr;
    Esfera *esfera = nullptr;
    Cabina *cabina = nullptr;

public:
    Cuerpo();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
              Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));
    void setRotacionCabina(float value);
    void setMaterial(Material m);
    void setColor(Tupla3f color);
};

#endif // CUERPO_H
