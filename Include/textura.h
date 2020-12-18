#ifndef TEXTURA_H
#define TEXTURA_H

#include "vector"
#include "Include/aux.h"

class Textura
{
private:
    GLuint textura_id = 0;
    std::vector<unsigned char> data;
    int width, height;

public:
    Textura(std::string archivo);
    void activar();
};

#endif // TEXTURA_H
