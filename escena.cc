

#include "Include/aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "Include/escena.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 7*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    visualizacion = INMEDIATO;
    coloreado = RELLENADO;
    tapas.first = true;
    tapas.second = true;
    rotaciones.first = false;
    rotaciones.second = false;
    inicializarLuces();
    actualizar_revolucion = false;
    iluminacion_activa = false;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
    glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

    Width  = UI_window_width/10;
    Height = UI_window_height/10;
    estado_dibujados.insert(GL_FILL);

   change_projection( float(UI_window_width)/float(UI_window_height) );
    glViewport( 0, 0, UI_window_width, UI_window_height );

    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    std::cout << "Bienvenido! Seleccione un menú" << std::endl <<
                 "\tO: Selección de objeto" << std::endl <<
                 "\tV: Selección de modo de visualización" << std::endl <<
                 "\tD: Selección de dibujado" << std::endl <<
                 "\tU: Tapas" << std::endl;
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    glDisable(GL_LIGHTING);
    ejes.draw();

    if (iluminacion_activa)
        glEnable(GL_LIGHTING);

    for (unsigned i = 0; i < luces.size(); ++i){
        if (estado_luces[i+1])
            luces[i]->activar();
    }

    foco = new Canon();
    foco->draw(visualizacion, estado_dibujados, coloreado);
    actualizar_revolucion = false;
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;

   switch( toupper(tecla) )
   {
       case 'Q' :
           if (modoMenu!=NADA)
               modoMenu=NADA;
           else {
               salir=true ;
           }
           break ;

           // ESTAMOS EN MODO SELECCION DE OBJETO
        case 'O' :
           std::cout << "Modo selección de objeto" << endl <<
                        "\tC: Activar cubo" << endl <<
                        "\tT: Activar tetraedro" << endl <<
                        "\tB: Activar Beethoven" << endl <<
                        "\tR: Activar ObjRevolucion" << endl <<
                        "\t3: Activar Esfera" << endl <<
                        "\t4: Activar Cono" << endl <<
                        "\t5: Activar Cilindro" << endl;
           modoMenu=SELOBJETO;
           break ;

        case 'C' :
           if (modoMenu == SELOBJETO)
               cubo_presente = !cubo_presente;
           break;

        case 'T' :
           if (modoMenu == SELOBJETO)
               tetraedro_presente = !tetraedro_presente;
           break;

        case 'B' :
            if (modoMenu == SELOBJETO){
                ply_presente = !ply_presente;
            }
            break;

        case 'R':
            if (modoMenu == SELOBJETO){
               obj_rev_presente = !obj_rev_presente;
               obj_rev2_presente = !obj_rev2_presente;
            }
           break;

        case '3':
            if (modoMenu == SELOBJETO){
              esfera_presente = !esfera_presente;
            }
          break;

        case '4':
            if (modoMenu == SELOBJETO){
             cono_presente = !cono_presente;
            }
         break;

        case '5':
            if (modoMenu == SELOBJETO){
             cilindro_presente = !cilindro_presente;
            }
         break;


           // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
       case 'V' :
           std::cout << "Modo selección de modo de visualización" << endl <<
                       "\tP: Activar modo puntos" << endl <<
                       "\tL: Activar modo lineas" << endl <<
                       "\tS: Activar modo rellenado" << endl <<
                       "\tA: Activar modo ajedrez" << endl <<
                       "\tI: Activar iluminación" << endl;
           modoMenu=SELVISUALIZACION;
           break ;
       case 'P':
           if (modoMenu == SELVISUALIZACION){
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_POINT) != estado_dibujados.end())
                   estado_dibujados.erase(GL_POINT);

               else
                   estado_dibujados.insert(GL_POINT);
           }

           break;
       case 'L':
           if (modoMenu == SELVISUALIZACION){
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_LINE) != estado_dibujados.end())
                   estado_dibujados.erase(GL_LINE);

               else
                   estado_dibujados.insert(GL_LINE);
           }
           break;
       case 'S':
           if (modoMenu == SELVISUALIZACION){
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_FILL) != estado_dibujados.end() &&
                       coloreado != AJEDREZ)
                   estado_dibujados.erase(GL_FILL);

               else
                   estado_dibujados.insert(GL_FILL);

               coloreado = RELLENADO;
           }
           break;
       case 'A':
           if (modoMenu == SELVISUALIZACION){
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_FILL) != estado_dibujados.end() &&
                       coloreado != RELLENADO)
                   estado_dibujados.clear();

               else{
                   estado_dibujados.clear();
                   estado_dibujados.insert(GL_FILL);
               }

               coloreado = AJEDREZ;
           }
           break;

        case 'I':
            std::cout << "Modo de iluminación" << endl <<
                        "\t0-7 Activar la luz i" << endl <<
                        "\tA: Modificar alpha" << endl <<
                        "\tB: Modificar beta" << endl <<
                        "\t>: Incrementar ángulo" << endl <<
                        "\t<: Reducir ángulo" << endl;
           iluminacion_activa = true;
           modoMenu = ILUMINACION;
           break;

           // ESTAMOS EN MODO SELECCION DE DIBUJADO
       case 'D' :
           std::cout << "Modo selección de dibujado" << endl <<
                       "\t1: Modo directo" << endl <<
                       "\t2: Modo diferido" << endl;
           modoMenu=SELDIBUJADO;
           break ;
           // COMPLETAR con los diferentes opciones de teclado
       case '1' :
           if (modoMenu == SELDIBUJADO)
               visualizacion = INMEDIATO;
           break;
       case '2' :
           if (modoMenu == SELDIBUJADO)
               visualizacion = VBO;
           break;


           //Interruptores de las tapaderas

        case 'U':
           std::cout << "Modo selección de dibujado" << endl <<
                       "\tN: Tapa inferior" << endl <<
                       "\tM: Tapa superior" << endl;
           modoMenu = TAPAS;
           break;

        case 'M':
            if (modoMenu == TAPAS){
                tapas.first = !tapas.first;
                actualizar_revolucion = true;
            }
           break;

        case 'N':
            if (modoMenu == TAPAS){
                tapas.second = !tapas.second;
                actualizar_revolucion = true;
            }
           break;

   }

   if (modoMenu == ILUMINACION){
       char tecla_m = toupper(tecla);
       int tecla_n = tecla_m - '0';
       if (tecla_m > '0' && tecla_m <= '2'){
           GLenum luzId = getIdLuz(tecla_m);

           if (!estado_luces[tecla_n])
               glEnable(luzId);

           else
               glDisable(luzId);

           estado_luces[tecla_n] = !estado_luces[tecla_n];
       }

       else if (tecla_m == '0'){
           if (!estado_luces[0])
                glEnable(GL_LIGHT0);

           else
               glDisable(GL_LIGHT0);

           estado_luces[0] = !estado_luces[0];
       }

       switch (toupper(tecla)) {
       case 'A':
           rotaciones.first = !rotaciones.first;
           std::cout << std::endl << "Modificar alpha: " << rotaciones.first << std::endl;
           break;

       case 'B':
           rotaciones.second = !rotaciones.second;
           std::cout << std::endl << "Modificar beta: " << rotaciones.second << std::endl;
           break;

       case '>':
           if (rotaciones.first){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloAlpha(0.5f);
               std::cout << static_cast<LuzDireccional*>(luces[1])->getAlpha() << endl;
           }

           else if (rotaciones.second){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(0.5f);
               std::cout << static_cast<LuzDireccional*>(luces[1])->getBeta() << endl;
           }

           break;

       case '<':
           if (rotaciones.first){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloAlpha(-0.5f);
               //std::cout << static_cast<LuzDireccional*>(luces[1])->getAlpha() << endl;
           }

           else if (rotaciones.second){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(-0.5f);
               //std::cout << static_cast<LuzDireccional*>(luces[1])->getBeta() << endl;
           }

           break;
       }
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
       case GLUT_KEY_LEFT:
         Observer_angle_y -= 5;
         break;
       case GLUT_KEY_RIGHT:
         Observer_angle_y += 5;
         break;
       case GLUT_KEY_UP:
         Observer_angle_x -= 5 ;
         break;
       case GLUT_KEY_DOWN:
         Observer_angle_x += 5 ;
         break;
       case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
       case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
    }

    //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

GLenum Escena::getIdLuz(unsigned char c){
    GLenum ret;

    switch(c){
    case '0':
        ret = GL_LIGHT0;
        break;

    case '1':
        ret = GL_LIGHT1;
        break;

    case '2':
        ret = GL_LIGHT2;
        break;

    case '3':
        ret = GL_LIGHT3;
        break;

    case '4':
        ret = GL_LIGHT4;
        break;

    case '5':
        ret = GL_LIGHT5;
        break;

    case '6':
        ret = GL_LIGHT6;
        break;

    case '7':
        ret = GL_LIGHT7;
        break;
    }

    return ret;
}

void Escena::inicializarLuces(){
    Tupla3f pos(0.0f, 150.0f, 150.0f);
    estado_luces.assign(8, false);

    LuzPosicional *luz1 = new LuzPosicional(pos, GL_LIGHT1, negro, naranja, celeste);
    luces.push_back(luz1);

    LuzDireccional *luz2 = new LuzDireccional(Tupla2f(0.0, 0.0), GL_LIGHT2, negro, blanco, blanco);
    luces.push_back(luz2);
}

Escena::~Escena(){
    for (unsigned i = 0; i < luces.size(); ++i)
        delete luces[i];
}
