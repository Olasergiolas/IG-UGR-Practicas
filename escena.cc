

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....

    visualizacion = INMEDIATO;
    coloreado = RELLENADO;

    cubo = new Cubo(100);
    cubo_presente = false;

    tetraedro = new Tetraedro();
    tetraedro_presente = false;

    ply_presente = false;

    obj_rev_presente = false;

    obj_test_presente = false;
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
    glShadeModel(GL_FLAT);
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
    ejes.draw();
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    if (cubo_presente)
        cubo->draw(visualizacion, estado_dibujados, coloreado);

    else if (tetraedro_presente)
        tetraedro->draw(visualizacion, estado_dibujados, coloreado);

    else if (ply_presente){
        glPushMatrix();
            glScalef(10.0,10.0,10.0);
            ply->draw(visualizacion, estado_dibujados, coloreado);
        glPopMatrix();
    }

    else if (obj_rev_presente){
        glPushMatrix();
            glScalef(50.0,50.0,50.0);
            obj_rev->draw(visualizacion, estado_dibujados, coloreado);
        glPopMatrix();
    }

    else if (obj_test_presente){
        glPushMatrix();
            glScalef(50.0,50.0,50.0);
            test->draw(visualizacion, estado_dibujados, coloreado);
        glPopMatrix();
    }

    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
    // cubo.draw()
    // o
    // tetraedro.draw()

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
                        "\tH: Activar Hormiga" << endl <<
                        "\tR: Activar ObjRevolucion" << endl;
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

                if (ply_presente)
                    ply = new ObjPLY("./plys/beethoven.ply");
            }
            break;

        case 'H' :
            if (modoMenu == SELOBJETO){
                ply_presente = !ply_presente;

                if (ply_presente)
                    ply = new ObjPLY("./plys/ant.ply");
            }
            break;

        case 'R':
           if (modoMenu == SELOBJETO){
               obj_rev_presente = !obj_rev_presente;

               if (obj_rev_presente)
                   obj_rev = new ObjRevolucion("./plys/peon.ply", 5, true, true);
           }
           break;

        case '9':                           //For testing purposes
          if (modoMenu == SELOBJETO){
              obj_test_presente = !obj_test_presente;

              if (obj_test_presente)
                  test = new Cilindro(5, 5, 1, 0.35);
          }
          break;


           // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
       case 'V' :
           std::cout << "Modo selección de modo de visualización" << endl <<
                       "\tP: Activar modo puntos" << endl <<
                       "\tL: Activar modo lineas" << endl <<
                       "\tS: Activar modo rellenado" << endl <<
                       "\tA: Activar modo ajedrez" << endl;
           modoMenu=SELVISUALIZACION;
           break ;
       case 'P':
           if (modoMenu == SELVISUALIZACION)
               if (estado_dibujados.find(GL_POINT) != estado_dibujados.end())
                   estado_dibujados.erase(GL_POINT);

               else
                   estado_dibujados.insert(GL_POINT);

           break;
       case 'L':
           if (modoMenu == SELVISUALIZACION)
               if (estado_dibujados.find(GL_LINE) != estado_dibujados.end())
                   estado_dibujados.erase(GL_LINE);

               else
                   estado_dibujados.insert(GL_LINE);
           break;
       case 'S':
           if (modoMenu == SELVISUALIZACION){
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
