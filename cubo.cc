#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "vector"

Cubo::Cubo(float lado)
{
    this->lado = lado;
    float pos = lado/2;

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    //Inicializamos tabla de vértices
    Tupla3f v0(-pos, -pos, pos);
    Tupla3f v1(pos, -pos, pos);
    Tupla3f v2(pos, pos, pos);
    Tupla3f v3(-pos, pos, pos);
    Tupla3f v4(-pos, -pos, -pos);
    Tupla3f v5(pos, -pos, -pos);
    Tupla3f v6(pos, pos, -pos);
    Tupla3f v7(-pos, pos, -pos);

    std::vector<Tupla3f> auxV{v0, v1, v2, v3, v4, v5, v6, v7};
    v = auxV;

    //Inicializamos tabla de triángulos

    //Frente
    Tupla3i c0(2, 0, 1);
    Tupla3i c1(2, 3, 0);

    //Trasera
    Tupla3i c2(7, 6, 5);
    Tupla3i c3(7, 5, 4);

    //Derecha
    Tupla3i c4(5, 6, 1);
    Tupla3i c5(1, 6, 2);

    //Izquierda
    Tupla3i c6(0, 3, 4);
    Tupla3i c7(7, 4, 3);

    //Superior
    Tupla3i c8(2, 6, 3);
    Tupla3i c9(3, 6, 7);

    //Inferior
    Tupla3i c10(4, 5, 1);
    Tupla3i c11(1, 0, 4);

    std::vector<Tupla3i> auxC{c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11};
    f = auxC;

    calcular_normales();
    inicializarColores();
    inicializarMaterial();
}
