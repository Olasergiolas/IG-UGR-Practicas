#include "Include/aux.h"
#include "Include/objrevolucion.h"
#include "Include/ply_reader.h"
#include "math.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, unsigned num_instancias, bool tapa_sup, bool tapa_inf,
                             bool tex_coord, bool invertir_sentido) :
    ObjRevolucion(getPerfiloriginal(archivo), num_instancias, tapa_sup, tapa_inf, tex_coord, invertir_sentido){}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, unsigned num_instancias, bool tapa_sup, bool tapa_inf,
                             bool tex_coord, bool invertir_sentido) {
    this->tapa_sup = tapa_sup;
    this->tapa_inf = tapa_inf;
    std::vector<Tupla3f> perfil_original;
    Tupla3f p_norte, p_sur;
    perfil_original = perfil;

   if ((*(perfil_original.end() - 1))(Y) > (*(perfil_original.begin()))(Y)){
        p_norte = *(perfil_original.end() - 1);
        p_sur = *(perfil_original.begin());
        s = CRECIENTE;
    }

    else{
        p_sur = *(perfil_original.end() - 1);
        p_norte = *(perfil_original.begin());
        s = DECRECIENTE;
    }

   if (p_norte(X) == 0 && p_norte(Z) == 0){
       if (s == CRECIENTE)
           perfil_original.erase(perfil_original.end() - 1);

       else
           perfil_original.erase(perfil_original.begin());
   }

   if (p_sur(X) == 0 && p_sur(Z) == 0){
       if (s == CRECIENTE)
           perfil_original.erase(perfil_original.begin());

       else
           perfil_original.erase(perfil_original.end() - 1);
   }

    tam_perfil = perfil_original.size();
    crearMalla(perfil_original, num_instancias, tex_coord, invertir_sentido);
    num_caras_no_tapas = f.size();
    crearTapas(tapa_sup, tapa_inf, p_sur, p_norte, num_instancias, perfil_original.size(), invertir_sentido);
    num_caras_total = f.size();
    inicializarColores();
    calcular_normales(tex_coord);
    inicializarMaterial();

    if (tex_coord)
        calcularTexCoord(num_instancias, perfil_original.size());
}

void ObjRevolucion::crearTapas(bool sup, bool inf, Tupla3f p_sur, Tupla3f p_norte,
                               unsigned num_instancias, unsigned num_vertices,
                               bool invertir_sentido){
    Tupla3i cara_aux;

    if (p_sur(X) != 0 || p_sur(Z) != 0){
        p_sur(X) = 0;
        p_sur(Z) = 0;
    }

    if (p_norte(X) != 0 || p_norte(Z) != 0){
        p_norte(X) = 0;
        p_norte(Z) = 0;
    }

    v.push_back(p_sur);
    v.push_back(p_norte);

    if (invertir_sentido | (s == CRECIENTE)){
        if (inf){
            for (unsigned i = 0; i < num_instancias; ++i){
                cara_aux(0) = v.size() - 2;
                cara_aux(2) = num_vertices * i;
                cara_aux(1) = num_vertices * ((i + 1)%num_instancias);
                f.push_back(cara_aux);
            }
        }

        if (sup){
            for (unsigned i = 0; i < num_instancias; ++i){

                cara_aux(0) = v.size() - 1;
                cara_aux(1) = num_vertices * (i + 1) - 1;

                if (i == num_instancias - 1)
                    cara_aux(2) = num_vertices - 1;             //Último punto de la primera instancia

                else
                    cara_aux(2) = num_vertices * (i + 2) - 1;

                f.push_back(cara_aux);
            }
        }
    }

    else{
        if (sup){
            for (unsigned i = 0; i < num_instancias; ++i){
                cara_aux(0) = v.size() - 1;
                cara_aux(1) = num_vertices * i;
                cara_aux(2) = num_vertices * ((i + 1)%num_instancias);
                f.push_back(cara_aux);
            }
        }

        if (inf){
            for (unsigned i = 0; i < num_instancias; ++i){

                cara_aux(0) = v.size() - 2;
                cara_aux(2) = num_vertices * (i + 1) - 1;

                if (i == num_instancias - 1)
                    cara_aux(1) = num_vertices - 1;             //Último punto de la primera instancia

                else
                    cara_aux(1) = num_vertices * (i + 2) - 1;

                f.push_back(cara_aux);
            }
        }
    }
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, unsigned num_instancias,
                               bool rotacion_completa, bool invertir_sentido) {
    Tupla3f vertice_aux;
    float old_x, old_z;
    float angulo;
    for (unsigned i = 0; i < num_instancias; ++i){
        angulo = (2*M_PI*i)/num_instancias;
        for (unsigned j = 0; j < perfil_original.size(); ++j){
            vertice_aux = perfil_original[j];
            old_x = vertice_aux(X);
            old_z = vertice_aux(Z);
            vertice_aux(X) = old_x * cos(angulo) + old_z * sin(angulo);
            vertice_aux(Z) = -old_x * sin(angulo) + old_z * cos(angulo);
            v.push_back(vertice_aux);
        }
    }

    //Duplicamos la primera costura para completar la rotación
    if (rotacion_completa){
        v.insert(v.end(), perfil_original.begin(), perfil_original.end());
        num_instancias++;
    }


    Tupla3i cara_aux;
    int a, b;
    for (unsigned i = 0; i < num_instancias; ++i){
        for (unsigned j = 0; j < perfil_original.size() - 1; ++j){
            a = perfil_original.size() * i + j;
            b = perfil_original.size() * ((i + 1)%num_instancias) + j;

            if (invertir_sentido | (s == CRECIENTE)){
                cara_aux(0) = a;
                cara_aux(1) = b;
                cara_aux(2) = b + 1;
                f.push_back(cara_aux);

                cara_aux(0) = a;
                cara_aux(1) = b + 1;
                cara_aux(2) = a + 1;
            }

            else{
                cara_aux(0) = a;
                cara_aux(2) = b;
                cara_aux(1) = b + 1;
                f.push_back(cara_aux);

                cara_aux(0) = a;
                cara_aux(2) = b + 1;
                cara_aux(1) = a + 1;
            }
            f.push_back(cara_aux);
        }
    }
}

std::vector<Tupla3f> ObjRevolucion::getPerfiloriginal(std::string archivo){
    std::vector<Tupla3f> perfil;
    ply::read_vertices(archivo, perfil);

    return perfil;
}

void ObjRevolucion::calcularTexCoord(unsigned num_instancias, unsigned num_v_perfil){
    float s = 0.0f;
    float t = 0.0f;
    float distancia = 0.0f;
    Tupla2f vector_perfil;
    std::vector<float> distancias;

    //Al repetir la última costura
    num_instancias++;
    for (unsigned i = 0; i < num_instancias; ++i){
        //calculo la x para todo el perfil
        s = (float)i/((float)num_instancias - 1);
        distancias.push_back(0.0f);

        if (distancias.size() == 1){
            for (unsigned j = 0; j < num_v_perfil; ++j){
                //relleno el vector de distancias
                vector_perfil(0) = v[(num_v_perfil * i) + (j + 1)](X) - v[(num_v_perfil * i) + j](X);
                vector_perfil(1) = v[(num_v_perfil * i) + (j + 1)](Y) - v[(num_v_perfil * i) + j](Y);
                distancia = vector_perfil.lengthSq();
                distancia += *(distancias.end() - 1);
                distancias.push_back(distancia);
            }
        }

        for (unsigned j = 0; j < num_v_perfil; ++j){
            //calculo y
            t = distancias[j]/distancias[num_v_perfil - 1];
            ct.push_back(Tupla2f(s, 1 - t));
        }
    }

    //For debugging purposes
    /*for (unsigned i = 0; i < num_instancias; ++i){
        for (unsigned j = 0; j < num_v_perfil; ++j){
            std::cout << "Inst: " << i << " V: " << j << " CT:" << ct[num_v_perfil*i + j] << std::endl;
        }

        if (i == 0){
            std::cout << "PRIMERA INSTANCIA" << std::endl;
            for (unsigned x = 0; x < num_v_perfil; ++x)
                std::cout << "V: " << v[i*num_v_perfil + x]  << std::endl;
        }

        if (i == num_instancias - 1){
            std::cout << "ULTIMA INSTANCIA" << std::endl;
            for (unsigned x = 0; x < num_v_perfil; ++x)
                std::cout << "V: " << v[i*num_v_perfil + x]  << std::endl;
        }
    }*/
}

//Redefinimos el método para obviar la instancia añadida para completar la rotación
void ObjRevolucion::calcular_normales(bool rotacion_completa){
    //Tabla de normales de las caras
    Tupla3f a, b, mc;
    Tupla3i caraActual;

    unsigned num_vertices = v.size();
    unsigned num_caras = f.size();

    if (rotacion_completa){
        num_vertices -= tam_perfil;    //Para no tener en cuenta la última instancia
        num_caras -= tam_perfil*2 - 2; //Ya que hay dos caras por vértice
    }

    std::vector<Tupla3f> tabla_normales_c;
    for (unsigned i = 0; i < num_caras; ++i){
        caraActual = f[i];

        a = v[caraActual(1)] - v[caraActual(0)];
        b = v[caraActual(2)] - v[caraActual(0)];
        mc = a.cross(b);
        if (mc.lengthSq() > 0)
            mc = mc.normalized();

        tabla_normales_c.push_back(mc);
    }

    //Tabla de normales de los vértices
    nv.assign(v.size(), Tupla3f(0.0, 0.0, 0.0));
    for (unsigned i = 0; i < num_caras; ++i){
        caraActual = f[i];
        nv[caraActual(0)] = nv[caraActual(0)] + tabla_normales_c[i];
        nv[caraActual(1)] = nv[caraActual(1)] + tabla_normales_c[i];
        nv[caraActual(2)] = nv[caraActual(2)] + tabla_normales_c[i];
    }

    for (unsigned i = 0; i < nv.size(); ++i){
        if (nv[i].lengthSq() > 0)
            nv[i] = nv[i].normalized();
    }
}

unsigned ObjRevolucion::getNumCaras(){
    unsigned caras = num_caras_no_tapas;

    if (tapa_sup)
        caras = num_caras_total;

    //std::cout << f.size() << ' ' << num_caras_total << ' ' << num_caras_no_tapas << std::endl;
    return caras;
}
