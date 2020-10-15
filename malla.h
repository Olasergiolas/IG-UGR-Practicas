// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {INMEDIATO, VBO} modo_visualizacion;
typedef enum {AJEDREZ, RELLENADO} modo_coloreado;

class Malla3D
{
   public:
    GLuint crearVBO(GLenum tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(GLuint id_vbo_ver, GLuint id_vbo_tri);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(modo_visualizacion v, GLenum m, modo_coloreado coloreado);

   void asignarColores(const std::vector<Tupla3f>& colores);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c ;
   std::vector<Tupla3f> c_ajedrez ;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
