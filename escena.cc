

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

    swordfish = new Swordfish();
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
                 "\tV: Selección de modo de visualización" << std::endl <<
                 "\tD: Selección de dibujado" << std::endl;
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

    swordfish->draw(visualizacion, estado_dibujados, coloreado);
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


         // Utilización de grados de libertad
        case 'M' :
           std::cout << "Menú de movimiento" << endl <<
                       "\t3: Rotación en X de alerones" << endl <<
                       "\t4: Rotación en Z de alerones" << endl <<
                       "\t5: Extensión de alas" << endl <<
                       "\t6: Rotación de la cápsula" << endl <<
                       "\t7: Movimiento automático" << endl;
            modoMenu = MOVIMIENTO;

            std::cout << std::endl;
            std::cout << "Interacción con el movimiento" << endl <<
                        "\t+: Incremento del valor" << endl <<
                        "\t-: Decremento del valor" << endl;

            break;

        case '3' :
            if (modoMenu == MOVIMIENTO)
                modoMenu = MOVIMIENTO_0;

            break;

       case '4' :
               if (modoMenu == MOVIMIENTO)
                   modoMenu = MOVIMIENTO_1;

               break;

       case '5' :
           if (modoMenu == MOVIMIENTO)
               modoMenu = MOVIMIENTO_2;

           break;

       case '6' :
           if (modoMenu == MOVIMIENTO)
               modoMenu = MOVIMIENTO_3;

           break;

       case '7' :
           if (modoMenu == MOVIMIENTO)
               modoMenu = MOVIMIENTO_AUTO;

           else if (modoMenu == MOVIMIENTO_AUTO)
               modoMenu = MOVIMIENTO;

           break;
   }

   if (modoMenu == MOVIMIENTO_0){
       switch (toupper(tecla)){
       case '+' :
           swordfish->setAlphaAlerones(10);
           break;

       case '-' :
           swordfish->setAlphaAlerones(-10);
           break;
       }
   }

   else if (modoMenu == MOVIMIENTO_1){
       switch (toupper(tecla)){
       case '+' :
           swordfish->setBetaAlerones(10);
           break;

       case '-' :
           swordfish->setBetaAlerones(-10);
           break;
       }
   }

   else if (modoMenu == MOVIMIENTO_2){
       switch (toupper(tecla)){
       case '-' :
           if (swordfish->getExtAlas() < 10.0f)
                swordfish->setExtAlas(10.0f);
           break;

       case '+' :
           if (swordfish->getExtAlas() > -50.0f)
           swordfish->setExtAlas(-10.0f);
           break;
       }
   }

   else if (modoMenu == MOVIMIENTO_3){
       switch (toupper(tecla)){
       case '+' :
           swordfish->setRotacionCapsula(10.0f);
           break;

       case '-' :
           swordfish->setRotacionCapsula(-10.0f);
           break;
       }
   }

   else if (modoMenu == MOVIMIENTO_AUTO){
       std::cout << std::endl << "Modificación de la animación" << endl <<
                   "\t+: Incrementar velocidad" << endl <<
                   "\t-: Reducir velocidad" << endl;

       std::cout << std::endl << "Selección del grado de libertad a alterar" << endl <<
                   "\t0: General" << endl <<
                   "\t1: Extensión alas" << endl <<
                   "\t2: Rotación alfa alerones" << endl <<
                   "\t3: Rotación beta alerones" << endl <<
                   "\t4: Rotación cápsula" << endl;

       animarModeloJerarquico();

       switch (toupper(tecla)){
       case '0' :
           gradoLibertad = 0;
           break;

       case '1' :
           gradoLibertad = 1;
           break;

       case '2' :
           gradoLibertad = 2;
           break;

       case '3' :
           gradoLibertad = 3;
           break;

       case '4' :
           gradoLibertad = 4;
           break;
       }

       switch (toupper(tecla)){
       case '+' :
           swordfish->increaseSpeedUp(gradoLibertad);
           break;

       case '-' :
           swordfish->reduceSpeedUp(gradoLibertad);
           break;
       }
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
           }

           else if (rotaciones.second){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(0.5f);
           }

           break;

       case '<':
           if (rotaciones.first){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloAlpha(-0.5f);
           }

           else if (rotaciones.second){
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(-0.5f);
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

void Escena::animarModeloJerarquico(){
    if (modoMenu == MOVIMIENTO_AUTO){

        if (gradoLibertad == 0){
            if ((swordfish->getExtAlas() -
                 (swordfish->getSpeedUp())) > -50.0f){
                swordfish->setExtAlas(-swordfish->getSpeedUp());
            }

            else{
                while (swordfish->getExtAlas() < 0)
                    swordfish->setExtAlas(swordfish->getSpeedUp());
            }

            swordfish->setAlphaAlerones(swordfish->getSpeedUp() * 10.0f);
            swordfish->setBetaAlerones(swordfish->getSpeedUp() * 10.0f);
            swordfish->setRotacionCapsula(swordfish->getSpeedUp() * 10.0f);
        }

        else{
            if ((swordfish->getExtAlas() -
                 (swordfish->getSpeedUp(1))) > -50.0f){
                swordfish->setExtAlas(-swordfish->getSpeedUp(1));
            }

            else{
                while (swordfish->getExtAlas() < 0)
                    swordfish->setExtAlas(swordfish->getSpeedUp(1));
            }

            swordfish->setAlphaAlerones(swordfish->getSpeedUp(2) * 10.0f);
            swordfish->setBetaAlerones(swordfish->getSpeedUp(3) * 10.0f);
            swordfish->setRotacionCapsula(swordfish->getSpeedUp(4) * 10.0f);
        }
    }
}

Escena::~Escena(){
    for (unsigned i = 0; i < luces.size(); ++i)
        delete luces[i];
}
