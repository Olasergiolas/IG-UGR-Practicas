#include "cilindro.h"
#include "objrevolucion.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura,
                   const float radio)
{
    std::vector<Tupla3f> perfil_original;
    Tupla3f punto_aux(radio, 0, 0);
    float incrementos = altura/num_vert_perfil;
    float altura_actual = 0;

    perfil_original.push_back(punto_aux);
    for (int i = 0; i < num_vert_perfil - 1; ++i){
        punto_aux(Y) = altura_actual + incrementos;

        altura_actual = punto_aux(Y);
        perfil_original.push_back(punto_aux);
    }

    crearMalla(perfil_original, num_instancias_perf);
    inicializarColores();
}
