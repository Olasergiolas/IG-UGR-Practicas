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

#include "Include/aux.h"
#include "set"
#include "Include/material.h"
#include "Include/textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {INMEDIATO, VBO} modo_visualizacion;
typedef enum {AJEDREZ, RELLENADO, ALT1, ALT2, COLOR_CODING} modo_coloreado;  //Para decidir si utilizamos los colores por defecto (c y c_ajedrez)
                                                               //o utilizamos colores alternativos. Útil para el dibujado simultáneo en modo alambre, fill...

class Malla3D
{
   public:
   GLuint crearVBO(GLenum tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void comprobarVBOs();

   void setMaterial(Material m);

   void set_textura(std::string archivo);

   void activar_textura();

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(modo_coloreado coloreado=RELLENADO, Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(modo_coloreado coloreado=RELLENADO, Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
             Tupla3f color = Tupla3f(0.0f, 0.0f, 0.0f));

   std::vector<Tupla3f> getColor(){return c;}

   Material getMaterial(){return *m;}

   void setColor(std::vector<Tupla3f> c){this->c = c;}

   void setColor(Tupla3f color);

   virtual unsigned getNumCaras(){return f.size();}

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   void inicializarColores();

   void inicializarMaterial();

   Material *m = nullptr;
   Textura *textura = nullptr;
   std::vector<Tupla3f> v;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f0;
   std::vector<Tupla3i> f1;
   std::vector<Tupla3f> c;
   std::vector<Tupla3f> c_ajedrez0;
   std::vector<Tupla3f> c_ajedrez1;
   std::vector<Tupla3f> c_alt_1;
   std::vector<Tupla3f> c_alt_2;
   std::vector<Tupla3f> c_code;
   std::vector<Tupla3f> nv;
   std::vector<Tupla2f> ct;
   GLuint id_ver_buffer = 0;
   GLuint id_tri_buffer = 0;
   GLuint id_tri0_buffer = 0;
   GLuint id_tri1_buffer = 0;
   GLuint id_c_buffer = 0;
   GLuint id_c_code_buffer = 0;
   GLuint id_ajedrez0_buffer = 0;
   GLuint id_ajedrez1_buffer = 0;
   GLuint id_ALT1_buffer = 0;
   GLuint id_ALT2_buffer = 0;
   GLuint id_norm_buffer = 0;


   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
