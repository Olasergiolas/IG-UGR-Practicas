#include "Include/canon.h"

Canon::Canon(){
    cilindro = new Cilindro(25, 25, 20, 10, true);
    base = new Cono(20, 50, 20, 10, true);

    paint();
}

void Canon::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
                 Tupla3f color){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslatef(-15.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0, 0, 1);
        glScalef(1.0f, 15.0f, 1.0f);
        cilindro->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90.0f, 0, 0, 1);
        glScalef(3.0f, 3.0f, 3.0f);
        base->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20.0f, -20.0f, 10.0);
        glRotatef(-90.0f, 1, 0, 0);
        cilindro->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
}

void Canon::setColor(Tupla3f color){
    cilindro->setColor(color);
    base->setColor(color);
}

void Canon::setMaterial(Material m){
    cilindro->setMaterial(m);
    base->setMaterial(m);
}

void Canon::paint(){
    Material m(negro, gris, blanco, 90.0f);
    base->setMaterial(m);
    cilindro->setMaterial(m);

    base->setColor(gris3);
    cilindro->setColor(gris3);
}
