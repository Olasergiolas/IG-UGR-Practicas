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
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado);
};

#endif // ALA_H
