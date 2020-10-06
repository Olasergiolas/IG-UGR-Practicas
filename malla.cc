#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(GLenum m)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

    glEnableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, m);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLenum m)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modo_visualizacion v, GLenum m)    //Según parámetro llama a los dos anteriores
{
   // completar .....(práctica 1)
    if (v == INMEDIATO)
        draw_ModoInmediato(m);

    else if (v == VBO)
        draw_ModoDiferido(m);
}

