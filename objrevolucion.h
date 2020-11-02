// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, unsigned num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> perfil, unsigned num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   void crearTapas(bool sup, bool inf, Tupla3f p_sur, Tupla3f p_norte, unsigned num_instancias,
                   unsigned num_vertices);

   void crearMalla(std::vector<Tupla3f> perfil_original, unsigned num_instancias);

} ;




#endif
