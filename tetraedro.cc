#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include "vector"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    Tupla3f v0(1, 1, 1);
    Tupla3f v1(1, -1, -1);
    Tupla3f v2(-1, 1, -1);
    Tupla3f v3(-1, -1, 1);

    std::vector<Tupla3f> auxV{v0, v1, v2, v3};
    v = auxV;

    Tupla3i c0(0, 1, 2);
    //Tupla3i c1();
    //Tupla3i c2();
    //Tupla3i c3();

    std::vector<Tupla3i> auxC{c0};
    f = auxC;

}

