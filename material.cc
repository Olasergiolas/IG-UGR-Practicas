#include "material.h"
#include "aux.h"

Material::Material(){}

Material::Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo)
{
    this->ambiente = ambiente;
    this->difuso = difuso;
    this->especular = especular;
    this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}

Tupla4f Material::getAmbiente(){
    return ambiente;
}

Tupla4f Material::getDifusa(){
    return difuso;
}

Tupla4f Material::getEspecular(){
    return especular;
}

float Material::getBrillo(){
    return brillo;
}
