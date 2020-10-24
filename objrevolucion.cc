#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"



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

    Tupla3f p_norte = *(perfil_original.end() - 1);
    Tupla3f p_sur = *(perfil_original.begin());

    if (p_norte(X) == 0 && p_norte(Z) == 0)
        perfil_original.erase(perfil_original.end() - 1);

    if (p_sur(X) == 0 && p_norte(Z) == 0)
        perfil_original.erase(perfil_original.begin());

    v = perfil_original;
    //crearMalla(perfil_original, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, unsigned num_instancias, bool tapa_sup, bool tapa_inf) {
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, unsigned num_instancias) {
    for (unsigned i = 0; i < num_instancias; ++i){
        for (unsigned j = 0; j < perfil_original.size(); ++j){

        }
    }
}
