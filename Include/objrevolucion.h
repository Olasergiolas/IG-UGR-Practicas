// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "Include/aux.h"
#include "Include/malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

typedef enum {CRECIENTE, DECRECIENTE} sentido;

class ObjRevolucion : public Malla3D
{
    protected:
        sentido s;

   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, unsigned num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> perfil, unsigned num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   void crearTapas(bool sup, bool inf, Tupla3f p_sur, Tupla3f p_norte, unsigned num_instancias,
                   unsigned num_vertices);

   void crearMalla(std::vector<Tupla3f> perfil_original, unsigned num_instancias);

   std::vector<Tupla3f> getPerfiloriginal(std::string archivo);
} ;




#endif
