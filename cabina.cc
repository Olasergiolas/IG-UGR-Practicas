#include "Include/cabina.h"

Cabina::Cabina(){
    cabina = new Cilindro(25, 25, 15, 10, std::pair<bool, bool>(true, true));
    semiesfera = new Esfera(20, 50, 10, std::pair<bool, bool>(true, true) ,false);
    alpha = 0.0f;

    Material m(negro, rojo, blanco, 90.0f);
    Material m1(negro, cobre, negro, 90.0f);

    cabina->setMaterial(m);
    semiesfera->setMaterial(m1);
}

void Cabina::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){
    glPushMatrix();
        glScalef(4.0f, 3.0f, 4.0f);
        cabina->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 40.0f, 0.0f);
        glRotatef(-alpha, 0, 0, 1);
        glScalef(3.5f, 3.5f, 3.5f);
        semiesfera->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
}

void Cabina::setAlpha(float value){
    alpha += value;
}
