#ifndef ALA_H
#define ALA_H

#include "Include/cubo.h"
#include "Include/tetraedro.h"

class Ala
{
private:
    Tetraedro *pico = nullptr;
    Cubo *cubo = nullptr;
    float alpha, beta;

public:
    Ala();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado, bool sentido,
              Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));
    void setAlpha(float value);
    void setBeta(float value);
    void setMaterial(Material m);
    void setColor(Tupla3f color);
};

#endif // ALA_H
