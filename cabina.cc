#include "Include/cabina.h"

Cabina::Cabina(){
    cabina = new Cilindro(25, 25, 15, 10, std::pair<bool, bool>(true, true));
    semiesfera = new Esfera(20, 50, 10, std::pair<bool, bool>(true, true) ,false);
    alpha = 90.0f;
}

void Cabina::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){
    glPushMatrix();
        glScalef(5.0f, 3.0f, 5.0f);
        cabina->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 40.0f, 0.0f);
        glRotatef(-alpha, 0, 0, 1);
        glScalef(4.0f, 4.0f, 4.0f);
        semiesfera->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
}
