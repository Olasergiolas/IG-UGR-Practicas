#include "Include/cilindro.h"
#include "Include/objrevolucion.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura,
                   const float radio, bool tapas)
{
    this->tapa_inf = tapas;
    this->tapa_sup = tapas;
    std::vector<Tupla3f> perfil_original;
    Tupla3f punto_aux(radio, 0, 0);
    Tupla3f p_norte, p_sur;
    float incrementos = altura/(num_vert_perfil - 1);
    float altura_actual = 0;
    s = CRECIENTE;

    perfil_original.push_back(punto_aux);
    for (int i = 0; i < num_vert_perfil - 1; ++i){
        punto_aux(Y) = altura_actual + incrementos;

        altura_actual = punto_aux(Y);
        perfil_original.push_back(punto_aux);
    }

    p_norte = perfil_original[perfil_original.size() - 1];
    p_sur = perfil_original[0];

    crearMalla(perfil_original, num_instancias_perf);
    num_caras_no_tapas = f.size();
    crearTapas(true, true, p_sur, p_norte, num_instancias_perf, num_vert_perfil);
    num_caras_total = f.size();
    inicializarColores();
    calcular_normales();
    inicializarMaterial();
}
