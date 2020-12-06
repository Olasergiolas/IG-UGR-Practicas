#include "Include/esfera.h"
#include "math.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, std::pair<bool, bool> tapas, bool completa)
{
    float angulo = M_PI/(num_vert_perfil-1);
    Tupla3f aux, p_norte, p_sur;
    int tope;
    float x_old = 0,
            y_old = radio;
    std::vector<Tupla3f> perfil_original;
    s = DECRECIENTE;

    perfil_original.push_back(Tupla3f(0, radio, 0));

    tope = (num_vert_perfil - 1)/2;
    if (completa)
        tope = num_vert_perfil - 1;

    for (int i = 0; i < tope; ++i){
        aux(X) = x_old * cos(angulo) + y_old * sin(angulo);
        aux(Y) = -x_old * sin(angulo) + y_old * cos(angulo);
        aux(Z) = 0;

        x_old = aux(X);
        y_old = aux(Y);

        perfil_original.push_back(aux);
    }

    p_norte = perfil_original[0];
    p_sur = perfil_original[perfil_original.size() - 1];

    perfil_original.erase(perfil_original.begin());

    if (completa)
        perfil_original.erase(perfil_original.end() - 1);

    crearMalla(perfil_original, num_instancias_perf);
    crearTapas(tapas.first, tapas.second, p_sur, p_norte, num_instancias_perf, perfil_original.size());
    inicializarColores();
    calcular_normales();
    inicializarMaterial();
}
