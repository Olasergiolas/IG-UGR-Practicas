#ifndef ESFERA_H
#define ESFERA_H
#include "Include/objrevolucion.h"


class Esfera : public ObjRevolucion
{
public:
    Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, std::pair<bool, bool> tapas);
};

#endif // ESFERA_H
