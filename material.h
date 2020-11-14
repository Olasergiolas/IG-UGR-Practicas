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
};

#endif // MATERIAL_H
