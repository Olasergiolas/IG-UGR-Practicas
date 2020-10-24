#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

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


