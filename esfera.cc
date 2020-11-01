#include "esfera.h"
#include "math.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
    float angulo = M_PI/num_vert_perfil;
    Tupla3f aux;
    float x_old = 0,
            y_old = radio;
    std::vector<Tupla3f> perfil_original;

    perfil_original.push_back(Tupla3f(0, radio, 0));
    for (int i = 0; i < num_vert_perfil; ++i){
        aux(X) = x_old * cos(angulo) + y_old * sin(angulo);
        aux(Y) = -x_old * sin(angulo) + y_old * cos(angulo);
        aux(Z) = 0;

        x_old = aux(X);
        y_old = aux(Y);

        perfil_original.push_back(aux);
    }

    crearMalla(perfil_original, num_instancias_perf);
    inicializarColores();
}
