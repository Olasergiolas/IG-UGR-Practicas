#include "aux.h"
#include "malla.h"
#include "vector"
#include "set"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

GLuint Malla3D::crearVBO(GLenum tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram){
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(tipo_vbo, id_vbo);

    glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

    glBindBuffer(tipo_vbo, 0);
    return id_vbo;
}

void Malla3D::comprobarVBOs(){
    if (id_ver_buffer == 0)
        id_ver_buffer = crearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());

    if (id_tri_buffer == 0)
        id_tri_buffer = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());

    if (id_c_buffer == 0)
        id_c_buffer = crearVBO(GL_ARRAY_BUFFER, c.size()*sizeof(float)*3, c.data());

    if (id_ajedrez_buffer == 0)
        id_ajedrez_buffer = crearVBO(GL_ARRAY_BUFFER, c_ajedrez.size()*sizeof(float)*3, c_ajedrez.data());

    if (id_ALT1_buffer == 0)
        id_ALT1_buffer = crearVBO(GL_ARRAY_BUFFER, c_alt_1.size()*sizeof(float)*3, c_alt_1.data());

    if (id_ALT2_buffer == 0)
        id_ALT2_buffer = crearVBO(GL_ARRAY_BUFFER, c_alt_2.size()*sizeof(float)*3, c_alt_2.data());


}

void Malla3D::draw_ModoInmediato(modo_coloreado coloreado)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

    glEnableClientState(GL_COLOR_ARRAY);

    if (coloreado == RELLENADO)
        glColorPointer(3, GL_FLOAT, 0, c.data());

    else if (coloreado == AJEDREZ)
        glColorPointer(3, GL_FLOAT, 0, c_ajedrez.data());

    else if (coloreado == ALT1)
        glColorPointer(3, GL_FLOAT, 0, c_alt_1.data());

    else
        glColorPointer(3, GL_FLOAT, 0, c_alt_2.data());

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(modo_coloreado coloreado)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

    comprobarVBOs();

    if (coloreado == AJEDREZ)
    	glBindBuffer(GL_ARRAY_BUFFER, id_ajedrez_buffer);

    else if (coloreado == RELLENADO)
    	glBindBuffer(GL_ARRAY_BUFFER, id_c_buffer);

    else if (coloreado == ALT1)
    	glBindBuffer(GL_ARRAY_BUFFER, id_ALT1_buffer);

    else
    	glBindBuffer(GL_ARRAY_BUFFER, id_ALT2_buffer);


    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, id_ver_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_tri_buffer);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado)    //Según parámetro llama a los dos anteriores
{
    modo_coloreado coloreado_final = coloreado;

    glEnableClientState(GL_COLOR_ARRAY);

        for (auto it = estado_dibujados.begin(); it != estado_dibujados.end(); ++it){

            glPolygonMode(GL_FRONT, *it);

            if (*it == GL_LINE)
                coloreado_final = ALT1;

            else if (*it == GL_POINT)
                coloreado_final = ALT2;

            else if (coloreado == AJEDREZ)
                coloreado_final = AJEDREZ;

            else
                coloreado_final = RELLENADO;


            if (v == VBO)
                draw_ModoDiferido(coloreado_final);

            else
                draw_ModoInmediato(coloreado_final);
        
    }

    glDisableClientState(GL_COLOR_ARRAY);
}
