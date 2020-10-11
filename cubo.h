// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "aux.h"
#include "vector"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Cubo : public Malla3D
{
   private:
    unsigned lado;

   public:
   Cubo(float l=1.0);
   void draw(modo_visualizacion v, GLenum m, modo_coloreado coloreado);
} ;




#endif
