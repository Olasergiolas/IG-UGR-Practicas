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

    float h = 100.0;

    Tupla3f v0(0.0, 0.0, (2*h)/3);
    Tupla3f v1(0.5773*h, 0, -(h/3));
    Tupla3f v2(-(0.5773*h), 0, -(h/3));
    Tupla3f v3(0, h, 0);

    std::vector<Tupla3f> auxV{v0, v1, v2, v3};
    v = auxV;

    Tupla3i c0(0, 2, 1);
    Tupla3i c1(3, 0, 1);
    Tupla3i c2(3, 1, 2);
    Tupla3i c3(3, 2, 0);

    std::vector<Tupla3i> auxC{c0, c1, c2, c3};
    f = auxC;
}

void Tetraedro::draw(modo_visualizacion v, GLenum m, modo_coloreado coloreado){
    Tupla3f rojo(1.0, 0.0, 0.0);
    Tupla3f negro(0.0, 0.0, 0.0);

    glEnableClientState(GL_COLOR_ARRAY);
    if (coloreado == AJEDREZ){
        std::vector<Tupla3f> auxColor{negro, rojo, negro, negro};
        c = auxColor;
        glColorPointer(3, GL_FLOAT, 0, c.data());
        Malla3D::draw(v, m);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    else
        Malla3D::draw(v, m);
}

