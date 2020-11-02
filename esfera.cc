#include "esfera.h"
#include "math.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, std::pair<bool, bool> tapas)
{
    float angulo = M_PI/(num_vert_perfil-1);
    Tupla3f aux, p_norte, p_sur;
    float x_old = 0,
            y_old = radio;
    std::vector<Tupla3f> perfil_original;

    perfil_original.push_back(Tupla3f(0, radio, 0));
    for (int i = 0; i < num_vert_perfil - 1; ++i){
        aux(X) = x_old * cos(angulo) + y_old * sin(angulo);
        aux(Y) = -x_old * sin(angulo) + y_old * cos(angulo);
        aux(Z) = 0;

        x_old = aux(X);
        y_old = aux(Y);

        perfil_original.push_back(aux);
    }

    p_sur = perfil_original[0];
    p_norte = perfil_original[perfil_original.size() - 1];

    perfil_original.erase(perfil_original.begin());
    perfil_original.erase(perfil_original.end() - 1);

    crearMalla(perfil_original, num_instancias_perf);
    crearTapas(tapas.first, tapas.second, p_sur, p_norte, num_instancias_perf, perfil_original.size());
    inicializarColores();
}
