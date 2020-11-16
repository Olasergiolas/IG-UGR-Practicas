#ifndef MATERIAL_H
#define MATERIAL_H

#include "tuplasg.h"

class Material
{
private:
    Tupla4f ambiente;
    Tupla4f especular;
    Tupla4f difuso;
    float brillo;

public:
    Material();
    Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo);
    void aplicar();
    Tupla4f getAmbiente();
    Tupla4f getDifusa();
    Tupla4f getEspecular();
    float getBrillo();
};

#endif // MATERIAL_H
