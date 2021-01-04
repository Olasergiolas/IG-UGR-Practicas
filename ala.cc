#include "Include/ala.h"

Ala::Ala(){
    cubo = new Cubo(10);
    pico = new Tetraedro();
    alpha = 0.0f;
    beta = 0.0f;

    paint();
}

void Ala::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado, bool sentido,
               Tupla3f color){
    glPushMatrix();

    if (sentido){
        glRotatef(beta, 1, 0, 0);
        glRotatef(alpha, 0, 0, 1);
    }

    else{
        glRotatef(-beta, 1, 0, 0);
        glRotatef(-alpha, 0, 0, 1);
    }

        glPushMatrix();
            glScalef(1.0f, 5.0f, 2.5f);
            cubo->draw(v, estado_dibujados, coloreado, color);
        glPopMatrix();

        glPushMatrix();
            glRotatef(90.0f, 1, 0, 0);
            glScalef(0.05f, 0.3f, 0.05f);
            pico->draw(v, estado_dibujados, coloreado, color);
        glPopMatrix();
    glPopMatrix();

    //plataforma
    glPushMatrix();
        glTranslatef(62.5f, 0.0f, 0.0f);
        glScalef(12.0f, 0.5f, 2.0f);
        cubo->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
}

void Ala::setAlpha(float value){
    alpha += value;
}

void Ala::setBeta(float value){
    beta += value;
}

void Ala::setColor(Tupla3f color){
    cubo->setColor(color);
    pico->setColor(color);
}

void Ala::setMaterial(Material m){
    cubo->setMaterial(m);
    pico->setMaterial(m);
}

void Ala::paint(){
    Material m(negro, rojo, blanco, 90.0f);
    cubo->setMaterial(m);
    pico->setMaterial(m);
}
