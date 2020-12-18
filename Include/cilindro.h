#ifndef CILINDRO_H
#define CILINDRO_H
#include "Include/objrevolucion.h"

class Cilindro : public ObjRevolucion
{
public:
    Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura,
             const float radio, std::pair<bool, bool> tapas);
};

#endif // CILINDRO_H
