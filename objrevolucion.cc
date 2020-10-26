#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "math.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, unsigned num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
    std::vector<Tupla3f> perfil_original;
    ply::read_vertices(archivo, perfil_original);

    Tupla3f p_sur = *(perfil_original.end() - 1);
    Tupla3f p_norte = *(perfil_original.begin());

    if (p_norte(X) == 0 && p_norte(Z) == 0)
        perfil_original.erase(perfil_original.end() - 1);

    if (p_sur(X) == 0 && p_norte(Z) == 0)
        perfil_original.erase(perfil_original.begin());

    crearMalla(perfil_original, num_instancias);
    crearTapas(tapa_sup, tapa_inf, p_sur, p_norte, num_instancias, perfil_original.size());




    Tupla3f rojo(1.0, 0.0, 0.0);
    Tupla3f negro(0.0, 0.0, 0.0);
    Tupla3f celeste(0.0, 0.8, 0.8);

    c.assign(v.size(), rojo);
    c_alt_1.assign(v.size(), celeste);
    c_alt_2.assign(v.size(), negro);

    std::vector<Tupla3f> ajedrez_aux;

    for (unsigned i = 0; i < v.size(); ++i){
        if (i%2)
            ajedrez_aux.push_back(rojo);

        else
            ajedrez_aux.push_back(negro);
    }

    c_ajedrez = ajedrez_aux;

}

void ObjRevolucion::crearTapas(bool sup, bool inf, Tupla3f p_sur, Tupla3f p_norte,
                               unsigned num_instancias, unsigned num_vertices){
    Tupla3i cara_aux;

    p_sur(X) = 0;
    p_sur(Z) = 0;
    p_norte(X) = 0;
    p_norte(Z) = 0;

    v.push_back(p_sur);
    v.push_back(p_norte);

    if (inf){
        for (unsigned i = 0; i < num_instancias; ++i){
            cara_aux(0) = v.size() - 1;
            cara_aux(2) = num_vertices * i;
            cara_aux(1) = num_vertices * ((i + 1)%num_instancias);
            f.push_back(cara_aux);
        }

    }
//std::cout << v.size() << std::endl;
    if (sup){
        for (unsigned i = 0; i < num_instancias; ++i){
            cara_aux(0) = v.size() - 2;
            cara_aux(1) = num_vertices * (i + 1) - 1;
            cara_aux(2) = (num_vertices * (i + 2) - 1)%v.size();
            f.push_back(cara_aux);
        }

    }
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, unsigned num_instancias, bool tapa_sup, bool tapa_inf) {

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, unsigned num_instancias) {
    Tupla3f vertice_aux;
    float old_x, old_z;
    float angulo;
    for (unsigned i = 0; i < num_instancias; ++i){
        angulo = (2*M_PI*i)/num_instancias;
        for (unsigned j = 0; j < perfil_original.size(); ++j){
            vertice_aux = perfil_original[j];
            old_x = vertice_aux(X);
            old_z = vertice_aux(Z);
            vertice_aux(X) = old_x * cos(angulo) + old_z * sin(angulo);
            vertice_aux(Z) = -old_x * sin(angulo) + old_z * cos(angulo);
            v.push_back(vertice_aux);
        }
    }

    Tupla3i cara_aux;
    int a, b;
    for (unsigned i = 0; i < num_instancias; ++i){
        for (unsigned j = 0; j < perfil_original.size() - 1; ++j){
            a = perfil_original.size() * i + j;
            b = perfil_original.size() * ((i + 1)%num_instancias) + j;
            cara_aux(0) = a;
            cara_aux(1) = b;
            cara_aux(2) = b + 1;
            f.push_back(cara_aux);

            cara_aux(0) = a;
            cara_aux(1) = b + 1;
            cara_aux(2) = a + 1;
            f.push_back(cara_aux);
        }
    }
}
