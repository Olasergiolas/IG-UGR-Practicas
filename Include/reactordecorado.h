#ifndef REACTORDECORADO_H
#define REACTORDECORADO_H

#include"cilindro.h"
#include"tetraedro.h"

class ReactorDecorado
{
private:
    Cilindro* reactor = nullptr;
    Tetraedro* aleron = nullptr;

public:
    ReactorDecorado();
    void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado);
};

#endif // REACTORDECORADO_H
