#include "Include/textura.h"
#include "Include/aux.h"
#include "Include/jpg_imagen.hpp"

Textura::Textura(std::string archivo)
{
    jpg::Imagen *pimg = NULL;
    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();
    data = pimg->leerPixels();
}

void Textura::activar(){
    if (textura_id == 0)
        glGenTextures(1, &textura_id);

    glBindTexture(GL_TEXTURE_2D, textura_id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB,
                      GL_UNSIGNED_BYTE, data);
}
