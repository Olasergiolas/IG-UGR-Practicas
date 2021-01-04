#include "Include/swordfish.h"

Swordfish::Swordfish(){
    cuerpo = new Cuerpo();
    reactor = new ReactorDecorado();
    canon = new Canon();
    ala = new Ala();
    ala1 = new Ala();
    ext_alas = 0.0f;
}

void Swordfish::draw(modo_visualizacion v, std::set<GLenum> estado_dibujados, modo_coloreado coloreado,
                     Tupla3f color){
    //Inicio tronco principal
    cuerpo->draw(v, estado_dibujados, coloreado, color);

    glPushMatrix();
        glTranslatef(50.0f, 0.0f, 0.0f);
        glScalef(0.25f, 0.25f, 0.25f);
        reactor->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-70.0f, -70.0f, 0.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        canon->draw(v, estado_dibujados, coloreado, color);
    glPopMatrix();
    //Fin tronco


    //Inicio alas
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, ext_alas);
        glTranslatef(-30.0f, 0.0f, -100.0f);
        glRotatef(-90.0f, 0, 1, 0);
        ala->draw(v, estado_dibujados, coloreado, true, color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -ext_alas);
        glTranslatef(-30.0f, 0.0f, 100.0f);
        glRotatef(180.0f, 0, 0, 1);
        glRotatef(180.0f, 0, 1, 0);
        glRotatef(-90.0f, 0, 1, 0);
        ala1->draw(v, estado_dibujados, coloreado, false, color);
    glPopMatrix();
    //Fin alas
}

void Swordfish::setExtAlas(float value){
    ext_alas += value;
}

float Swordfish::getExtAlas(){
    return ext_alas;
}

void Swordfish::setAlphaAlerones(float value){
    ala->setAlpha(value);
    ala1->setAlpha(value);
}

void Swordfish::setBetaAlerones(float value){
    ala->setBeta(value);
    ala1->setBeta(value);
}

void Swordfish::setRotacionCapsula(float value){
    cuerpo->setRotacionCabina(value);
}

int Swordfish::getSpeedUp(unsigned ind){
    return partSpeedUp[ind];
}

void Swordfish::increaseSpeedUp(unsigned ind){
    partSpeedUp[ind] += 0.5f;
    std::cout << std::endl << partSpeedUp[ind] << std::endl;
}

void Swordfish::reduceSpeedUp(unsigned ind){
    if (partSpeedUp[ind] > 0.5f){
        partSpeedUp[ind] -= 0.5f;
    }


    std::cout << std::endl << partSpeedUp[ind] << std::endl;
}

void Swordfish::setColor(Tupla3f color){
    cuerpo->setColor(color);
    reactor->setColor(color);
    canon->setColor(color);
    ala->setColor(color);
    ala1->setColor(color);
}

void Swordfish::setMaterial(Material m, Material mat_aleron){
    cuerpo->setMaterial(m);
    reactor->setMaterial(m, mat_aleron);
    canon->setMaterial(m);
    ala->setMaterial(m);
    ala1->setMaterial(m);
}

void Swordfish::paint(){
    Material rojo_mat(negro, rojo, blanco, 90.0f);
    Material gris_mat(negro, gris, blanco, 90.0f);
    Material gris_mat1(negro, gris, gris, 90.0f);


    cuerpo->setColor(gris3);
    reactor->setColor(gris3);
    canon->setColor(gris3);
    ala->setColor(gris3);
    ala1->setColor(gris3);

    cuerpo->setMaterial(rojo_mat);
    reactor->setMaterial(gris_mat1, rojo_mat);
    canon->setMaterial(gris_mat);
    ala->setMaterial(rojo_mat);
    ala1->setMaterial(rojo_mat);

}
