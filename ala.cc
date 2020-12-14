#include "Include/ala.h"

Ala::Ala(){
    cubo = new Cubo(10);
    pico = new Tetraedro();
    alpha = 0.0f;
    beta = 0.0f;

    Material m(negro, rojo, blanco, 90.0f);
    cubo->setMaterial(m);
    pico->setMaterial(m);
}

void Ala::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){
    glPushMatrix();
        glRotatef(beta, 1, 0, 0);
        glRotatef(alpha, 0, 0, 1);

        glPushMatrix();
            glScalef(0.5f, 5.0f, 2.5f);
            cubo->draw(v, estado_dibujados, coloreado);
        glPopMatrix();

        glPushMatrix();
            glRotatef(90.0f, 1, 0, 0);
            glScalef(0.05f, 0.3f, 0.05f);
            pico->draw(v, estado_dibujados, coloreado);
        glPopMatrix();
    glPopMatrix();

    //plataforma
    glPushMatrix();
        glTranslatef(60.0f, 0.0f, 0.0f);
        glScalef(12.0f, 0.5f, 1.0f);
        cubo->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
}

void Ala::setAlpha(float value){
    alpha += value;
}

void Ala::setBeta(float value){
    beta += value;
}
