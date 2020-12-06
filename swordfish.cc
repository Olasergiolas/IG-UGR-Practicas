#include "Include/swordfish.h"

Swordfish::Swordfish(){
    cuerpo = new Cuerpo();
    reactor = new ReactorDecorado();
    canon = new Canon();
    ala = new Ala();
    ext_alas = 0.0f;
}

void Swordfish::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado){
    //Inicio tronco principal
    cuerpo->draw(v, estado_dibujados, coloreado);

    glPushMatrix();
        glTranslatef(50.0f, 0.0f, 0.0f);
        glScalef(0.25f, 0.25f, 0.25f);
        reactor->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-70.0f, -70.0f, 0.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        canon->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
    //Fin tronco


    //Inicio alas
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, ext_alas);
        glTranslatef(-30.0f, 0.0f, -100.0f);
        glRotatef(-90.0f, 0, 1, 0);
        ala->draw(v, estado_dibujados, coloreado);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -ext_alas);
        glScalef(1.0f, 1.0f, -1.0f);
        glTranslatef(-30.0f, 0.0f, -100.0f);
        glRotatef(-90.0f, 0, 1, 0);
        ala->draw(v, estado_dibujados, coloreado);
    glPopMatrix();
    //Fin alas
}

void Swordfish::setExtAlas(float value){
    //if (value < 30.0f && value >= 0.0f)

    if (value > 0.0f && ext_alas < 30.0f)
        ext_alas += value;

    //else if (value < 0.0f && ext_alas > 30.0f)


}

void Swordfish::setAlphaAlerones(float value){
    ala->setAlpha(value);
}

void Swordfish::setBetaAlerones(float value){
    ala->setBeta(value);
}

void Swordfish::setRotacionCapsula(float value){
    cuerpo->setRotacionCabina(value);
}
