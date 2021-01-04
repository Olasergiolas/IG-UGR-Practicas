#include "Include/reactordecorado.h"

ReactorDecorado::ReactorDecorado()
{
    reactor = new Cilindro(25, 25, 50, 25, std::pair<bool, bool>(true, true));
    aleron = new Tetraedro();

    Material m(negro, gris, gris, 90.0f);
    Material m1(negro, rojo, blanco, 90.0f);

    reactor->setMaterial(m);
    aleron->setMaterial(m1);
}

void ReactorDecorado::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
                           Tupla3f color){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(-90.0f, 0, 0, 1);
        glScalef(5.0f, 5.0f, 5.0f);
        reactor->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(120, 100, 0);
        glRotatef(-25.0f, 0, 0, 1);
        aleron->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0,-1.0,1.0);
        glTranslatef(120, 100, 0);
        glRotatef(-25.0f, 0, 0, 1);
        aleron->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
}

void ReactorDecorado::setColor(Tupla3f color){
    reactor->setColor(color);
    aleron->setColor(color);
}

void ReactorDecorado::setMaterial(Material m1, Material m2){
    reactor->setMaterial(m1);
    aleron->setMaterial(m2);
}
