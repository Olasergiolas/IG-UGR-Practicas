#include "aux.h"
#include "malla.h"
#include "vector"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

static const GLfloat colores2[] = {
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.5, 0.5, 0.5,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0
};

GLuint Malla3D::crearVBO(GLenum tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram){
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(tipo_vbo, id_vbo);

    glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

    glBindBuffer(tipo_vbo, 0);
    return id_vbo;
}

void Malla3D::draw_ModoInmediato(GLenum m)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

    glEnableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_COLOR_ARRAY);
    glShadeModel(GL_FLAT);
    glColorPointer(3, GL_FLOAT, 0, colores2);

    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLenum m, GLuint id_vbo_ver, GLuint id_vbo_tri)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

    if (id_vbo_ver == 0)
        id_vbo_ver = crearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());

    if (id_vbo_tri == 0)
        id_vbo_tri = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());

    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modo_visualizacion v, GLenum m)    //Según parámetro llama a los dos anteriores
{
   // completar .....(práctica 1)

    glPolygonMode(GL_FRONT_AND_BACK, m);
    if (v == INMEDIATO)
        draw_ModoInmediato(m);

    else if (v == VBO)
        draw_ModoDiferido(m, 0, 0);
}

