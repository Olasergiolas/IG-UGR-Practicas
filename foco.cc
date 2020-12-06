#include "Include/foco.h"

Foco::Foco()
{
    cono = new Cono(20, 50, 20, 10, std::pair<bool, bool>(true, true));
    esfera = new Esfera(20, 50, 10, std::pair<bool, bool>(true, true), true);
}


void Foco::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glRotatef(-90.0f, 0, 0, 1);
        glScalef(0.5f, 0.5f, 0.5f);
        cono->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glScalef(0.25f,0.25f,0.25f);
        esfera->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

}
