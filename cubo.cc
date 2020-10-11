#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "vector"

//Dibujar el cubo a papel y ver dónde están los vértices del cubo

Cubo::Cubo(float lado)
{
    this->lado = lado;

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    //Inicializamos tabla de vértices
    Tupla3f v0(-lado, -lado, lado);
    Tupla3f v1(lado, -lado, lado);
    Tupla3f v2(lado, lado, lado);
    Tupla3f v3(-lado, lado, lado);
    Tupla3f v4(-lado, -lado, -lado);
    Tupla3f v5(lado, -lado, -lado);
    Tupla3f v6(lado, lado, -lado);
    Tupla3f v7(-lado, lado, -lado);

    std::vector<Tupla3f> auxV{v0, v1, v2, v3, v4, v5, v6, v7};
    v = auxV;

    //Inicializamos tabla de triángulos

    //Frente
    Tupla3i c0(0, 1, 2);
    Tupla3i c1(2, 3, 0);

    //Trasera
    Tupla3i c2(7, 6, 5);
    Tupla3i c3(5, 4, 7);

    //Derecha
    Tupla3i c4(1, 5, 6);
    Tupla3i c5(6, 2, 1);

    //Izquierda
    Tupla3i c6(4, 0, 3);
    Tupla3i c7(3, 7, 4);

    //Superior
    Tupla3i c8(3, 2, 6);
    Tupla3i c9(6, 7, 3);

    //Inferior
    Tupla3i c10(4, 5, 1);
    Tupla3i c11(1, 0, 4);

    std::vector<Tupla3i> auxC{c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11};
    f = auxC;
}

void Cubo::draw(modo_visualizacion v, GLenum m, bool ajedrez){
    if (ajedrez){
        Tupla3f color0(0.0, 0.0, 0.0);
        Tupla3f color1(0.0, 0.0, 0.0);
        Tupla3f color2(1.0, 0.0, 0.0);
        Tupla3f color3(0.0, 0.0, 0.0);
        Tupla3f color4(1.0, 0.0, 0.0);
        Tupla3f color5(1.0, 0.0, 0.0);
        Tupla3f color6(1.0, 0.0, 0.0);
        Tupla3f color7(0.0, 0.0, 0.0);
        Tupla3f color8(0.0, 0.0, 0.0);
        Tupla3f color9(0.0, 0.0, 0.0);
        Tupla3f color10(0.0, 0.0, 0.0);
        Tupla3f color11(0.0, 0.0, 0.0);

        std::vector<Tupla3f> auxColor{color0, color1, color2, color3, color4, color5,
                    color6, color7, color8, color9, color10, color11};

        c = auxColor;

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, c.data());
        Malla3D::draw(v, m);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    else
        Malla3D::draw(v, m);
}
