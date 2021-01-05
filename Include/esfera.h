#ifndef ESFERA_H
#define ESFERA_H
#include "Include/objrevolucion.h"


class Esfera : public ObjRevolucion
{
public:
    Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, bool tapas,
           bool completa=true);

    bool getTapas(){return tapa_sup;}
};

#endif // ESFERA_H
