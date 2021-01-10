#include "Include/cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura,
           const float radio, bool tapas)
{
    this->tapa_sup = tapas;
    this->tapa_inf = tapas;
    Tupla3f p_norte(0, altura, 0);
    Tupla3f p_sur(radio, 0, 0);
    Tupla3f aux;
    std::vector<Tupla3f> perfil_original;
    float hipotenusa = sqrt(pow(altura, 2) + pow(radio, 2));
    float incrementos_x = radio/(num_vert_perfil - 1);
    float incrementos_hip = hipotenusa/(num_vert_perfil - 1);
    float base_actual = 0;
    float hip_actual = 0;
    float h_actual = 0;
    s = CRECIENTE;

    perfil_original.push_back(p_sur);
    for (int i = 0; i < num_vert_perfil - 1; ++i){  //Para que no añada p_norte
        base_actual += incrementos_x;
        hip_actual += incrementos_hip;

        h_actual = sqrt(pow(hip_actual, 2) - pow(base_actual, 2));

        aux(X) = radio - base_actual;
        aux(Y) = h_actual;
        aux(Z) = 0;

        perfil_original.push_back(aux);
    }
    perfil_original.erase(perfil_original.end() - 1);

    crearMalla(perfil_original, num_instancias_perf);
    num_caras_no_tapas = f.size();
    crearTapas(true, true, p_sur, p_norte, num_instancias_perf, perfil_original.size());
    num_caras_total = f.size();
    inicializarColores();
    calcular_normales();
    inicializarMaterial();
}
