#include "Include/cuerpo.h"

Cuerpo::Cuerpo(){
    morro = new Tetraedro();
    foco = new Foco();
    esfera = new Esfera(25, 50, 10, std::pair<bool, bool>(true, true));
    cabina = new Cabina();

    paint();
}

void Cuerpo::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
                  Tupla3f color){

    //Inicio morro
    glPushMatrix();
        glRotatef(90.0f, 1, 0, 0);
        glRotatef(90.0f, 0, 0, 1);
        glScalef(1.0f, 2.0f, 1.0f);
        morro->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50.0f, 30.0f, 20.0f);
        foco->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50.0f, 30.0f, -20.0f);
        foco->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
    //Fin morro

    glPushMatrix();
        glTranslatef(-50.0f, -70.0f, 0.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        esfera->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30.0f, 0.0f, 0.0f);
        //glScalef(3.0f, 3.0f, 3.0f);
        cabina->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
}

void Cuerpo::setRotacionCabina(float value){
    cabina->setAlpha(value);
}

void Cuerpo::setColor(Tupla3f color){
    morro->setColor(color);
    foco->setColor(color);
    esfera->setColor(color);
    cabina->setColor(color);
}

void Cuerpo::setMaterial(Material m){
    morro->setMaterial(m);
    foco->setMaterial(m);
    esfera->setMaterial(m);
    cabina->setMaterial(m);
}

void Cuerpo::paint(){
    Material m(negro, rojo, blanco, 90.0f);
    morro->setMaterial(m);
    esfera->setMaterial(m);
    foco->paint();
    cabina->paint();
}
