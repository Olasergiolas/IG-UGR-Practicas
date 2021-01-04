#include "Include/foco.h"

Foco::Foco()
{
    cono = new Cono(20, 50, 20, 10, std::pair<bool, bool>(true, true));
    esfera = new Esfera(20, 50, 10, std::pair<bool, bool>(true, true), true);

    paint();
}


void Foco::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
                Tupla3f color){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glRotatef(-90.0f, 0, 0, 1);
        glScalef(0.5f, 0.5f, 0.5f);
        cono->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glScalef(0.25f,0.25f,0.25f);
        esfera->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

}

void Foco::setColor(Tupla3f color){
    cono->setColor(color);
    esfera->setColor(color);
}

void Foco::setMaterial(Material m){
    cono->setMaterial(m);
    esfera->setMaterial(m);
}

void Foco::paint(){
    Material m(negro, gris, blanco, 90.0f);
    Material m1(negro, blanco, blanco, 90.0f);
    cono->setMaterial(m);
    esfera->setMaterial(m1);
}
