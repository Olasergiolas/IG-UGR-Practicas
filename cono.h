#ifndef CONO_H
#define CONO_H
#include "objrevolucion.h"


class Cono : public ObjRevolucion
{
public:
    Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura,
         const float radio);
};

#endif // CONO_H
