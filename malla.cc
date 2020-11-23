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

    if (id_tri0_buffer == 0)
        id_tri0_buffer = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f0.size()*sizeof(int)*3, f0.data());

    if (id_tri1_buffer == 0)
        id_tri1_buffer = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f1.size()*sizeof(int)*3, f1.data());

    if (id_c_buffer == 0)
        id_c_buffer = crearVBO(GL_ARRAY_BUFFER, c.size()*sizeof(float)*3, c.data());

    if (id_ajedrez0_buffer == 0)
        id_ajedrez0_buffer = crearVBO(GL_ARRAY_BUFFER, c_ajedrez0.size()*sizeof(float)*3, c_ajedrez0.data());

    if (id_ajedrez1_buffer == 0)
        id_ajedrez1_buffer = crearVBO(GL_ARRAY_BUFFER, c_ajedrez1.size()*sizeof(float)*3, c_ajedrez1.data());

    if (id_ALT1_buffer == 0)
        id_ALT1_buffer = crearVBO(GL_ARRAY_BUFFER, c_alt_1.size()*sizeof(float)*3, c_alt_1.data());

    if (id_ALT2_buffer == 0)
        id_ALT2_buffer = crearVBO(GL_ARRAY_BUFFER, c_alt_2.size()*sizeof(float)*3, c_alt_2.data());

    if (id_norm_buffer == 0)
        id_norm_buffer = crearVBO(GL_ARRAY_BUFFER, nv.size()*sizeof(float)*3, nv.data());
}

void Malla3D::draw_ModoInmediato(modo_coloreado coloreado)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glNormalPointer(GL_FLOAT, 0, nv.data());

    if (coloreado == AJEDREZ){
        if (f0.empty() || f1.empty()){
            for (unsigned i = 0; i < f.size(); ++i){
                if (i%2)
                    f0.push_back(f[i]);
                else
                    f1.push_back(f[i]);
            }
        }

        glColorPointer(3, GL_FLOAT, 0, c_ajedrez0.data());
        glDrawElements(GL_TRIANGLES, f0.size()*3, GL_UNSIGNED_INT, f0.data());
        glColorPointer(3, GL_FLOAT, 0, c_ajedrez1.data());
        glDrawElements(GL_TRIANGLES, f1.size()*3, GL_UNSIGNED_INT, f1.data());
    }

    else{
        if (coloreado == RELLENADO)
            glColorPointer(3, GL_FLOAT, 0, c.data());

        else if (coloreado == ALT1)
            glColorPointer(3, GL_FLOAT, 0, c_alt_1.data());

        else
            glColorPointer(3, GL_FLOAT, 0, c_alt_2.data());

        glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(modo_coloreado coloreado)
{
    if (f0.empty() || f1.empty()){
        for (unsigned i = 0; i < f.size(); ++i){
            if (i%2)
                f0.push_back(f[i]);
            else
                f1.push_back(f[i]);
        }
    }

    comprobarVBOs();
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, id_ver_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, id_norm_buffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableClientState(GL_VERTEX_ARRAY);

    if (coloreado == AJEDREZ){

        glBindBuffer(GL_ARRAY_BUFFER, id_ajedrez0_buffer);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_tri0_buffer);
        glDrawElements(GL_TRIANGLES, 3*f0.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, id_ajedrez1_buffer);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_tri1_buffer);
        glDrawElements(GL_TRIANGLES, 3*f1.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    else{

        if (coloreado == RELLENADO)
            glBindBuffer(GL_ARRAY_BUFFER, id_c_buffer);

        else if (coloreado == ALT1)
            glBindBuffer(GL_ARRAY_BUFFER, id_ALT1_buffer);

        else
            glBindBuffer(GL_ARRAY_BUFFER, id_ALT2_buffer);

        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_tri_buffer);
        glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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

            if (m != nullptr)
                m->aplicar();

            if (v == VBO)
                draw_ModoDiferido(coloreado_final);

            else
                draw_ModoInmediato(coloreado_final);
        
    }

    glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::inicializarColores(){
    c.assign(v.size(), rojo3);
    c_alt_1.assign(v.size(), celeste3);
    c_alt_2.assign(v.size(), negro3);
    c_ajedrez0.assign(v.size(), verde3);
    c_ajedrez1.assign(v.size(), naranja3);
}

void Malla3D::calcular_normales(){
    //Tabla de normales de las caras
    Tupla3f a, b, mc;
    Tupla3i caraActual;
    std::vector<Tupla3f> tabla_normales_c;
    for (unsigned i = 0; i < f.size(); ++i){
        caraActual = f[i];

        a = v[caraActual(1)] - v[caraActual(0)];
        b = v[caraActual(2)] - v[caraActual(0)];
        mc = a.cross(b);
        mc = mc.normalized();

        tabla_normales_c.push_back(mc);
    }

    //Tabla de normales de los vértices
    nv.assign(v.size(), Tupla3f(0.0, 0.0, 0.0));
    for (unsigned i = 0; i < f.size(); ++i){
        caraActual = f[i];
        nv[caraActual(0)] = nv[caraActual(0)] + tabla_normales_c[i];
        nv[caraActual(1)] = nv[caraActual(1)] + tabla_normales_c[i];
        nv[caraActual(2)] = nv[caraActual(2)] + tabla_normales_c[i];
    }

    for (unsigned i = 0; i < nv.size(); ++i)
        nv[i] = nv[i].normalized();

}

void Malla3D::inicializarMaterial(){
    Material aux(negro, rosa, blanco, 80.0);
    setMaterial(aux);
}

void Malla3D::setMaterial(Material m){
    this->m = new Material(m.getAmbiente(), m.getDifusa(), m.getEspecular(), m.getBrillo());
}
