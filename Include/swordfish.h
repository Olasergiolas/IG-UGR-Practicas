#ifndef SWORDFISH_H
#define SWORDFISH_H

#include "Include/cuerpo.h"
#include "Include/reactordecorado.h"
#include "Include/canon.h"
#include "Include/ala.h"

class Swordfish
{
private:
    Cuerpo *cuerpo = nullptr;
    ReactorDecorado *reactor = nullptr;
    Canon *canon = nullptr;
    Ala *ala = nullptr;
    Ala *ala1 = nullptr;
    float ext_alas;
    float partSpeedUp[5] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

public:
    Swordfish();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado);
    void setExtAlas(float value);
    void setAlphaAlerones(float value);
    void setBetaAlerones(float value);
    void setRotacionCapsula(float value);
    float getExtAlas();
    int getSpeedUp(unsigned ind=0);
    void increaseSpeedUp(unsigned ind=0);
    void reduceSpeedUp(unsigned ind=0);
};

#endif // SWORDFISH_H
