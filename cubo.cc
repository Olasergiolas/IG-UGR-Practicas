#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "vector"

//Dibujar el cubo a papel y ver dónde están los vértices del cubo

Cubo::Cubo(float lado)
{
    lado = this->lado;

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    //Inicializamos tabla de vértices
    Tupla3f v0(1.0, -1.0, 1.0);
    Tupla3f v1(1.0, 1.0, 1.0);
    Tupla3f v2(-1.0, 1.0, 1.0);
    Tupla3f v3(-1.0, -1.0, 1.0);
    Tupla3f v4(1.0, -1.0, -1.0);
    Tupla3f v5(1.0, 1.0, -1.0);
    Tupla3f v6(-1.0, 1.0, -1.0);
    Tupla3f v7(-1.0, -1.0, -1.0);

    std::vector<Tupla3f> auxV{v0, v1, v2, v3, v4, v5, v6, v7};
    v = auxV;

    //Inicializamos tabla de triángulos
    Tupla3i c0(0, 1, 3);
    Tupla3i c1(1, 2, 3);
    Tupla3i c2(4, 5, 0);
    Tupla3i c3(5, 1, 0);
    Tupla3i c4(7, 4, 5);
    Tupla3i c5(7, 5, 6);
    Tupla3i c6(7, 6, 3);
    Tupla3i c7(6, 2, 3);
    Tupla3i c8(1, 5, 2);
    Tupla3i c9(5, 6, 2);
    Tupla3i c10(0, 4, 3);
    Tupla3i c11(4, 7, 3);

    std::vector<Tupla3i> auxC{c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11};
    f = auxC;
}

