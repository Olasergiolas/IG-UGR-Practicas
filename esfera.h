#ifndef ESFERA_H
#define ESFERA_H
#include "objrevolucion.h"


class Esfera : public ObjRevolucion
{
public:
    Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio);
};

#endif // ESFERA_H
