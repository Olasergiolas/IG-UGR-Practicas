#include "Include/cuerpo.h"

Cuerpo::Cuerpo(){
    morro = new Tetraedro();
    foco = new Foco();
    esfera = new Esfera(25, 50, 10, std::pair<bool, bool>(true, true));
    cabina = new Cabina();

    Material m(negro, rojo, blanco, 90.0f);
    morro->setMaterial(m);
    esfera->setMaterial(m);
}

void Cuerpo::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){

    //Inicio morro
    glPushMatrix();
        glRotatef(90.0f, 1, 0, 0);
        glRotatef(90.0f, 0, 0, 1);
        glScalef(1.0f, 2.0f, 1.0f);
        morro->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50.0f, 30.0f, 20.0f);
        foco->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50.0f, 30.0f, -20.0f);
        foco->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
    //Fin morro

    glPushMatrix();
        glTranslatef(-50.0f, -70.0f, 0.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        esfera->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30.0f, 0.0f, 0.0f);
        //glScalef(3.0f, 3.0f, 3.0f);
        cabina->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
}

void Cuerpo::setRotacionCabina(float value){
    cabina->setAlpha(value);
}
