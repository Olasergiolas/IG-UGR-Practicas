

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
    ultima_tecla = ' ';
    gradoLibertad = 0;
    tapas.first = true;
    tapas.second = true;
    rotaciones.first = false;
    rotaciones.second = false;
    anima_luces = false;

    std::pair<std::string, Tupla3f> aux_pair;

    cubo = new Cubo(100);
    Material aux(negro, blanco, blanco, 90.0);
    cubo->setMaterial(aux);
    cubo->set_textura("text-madera.jpg");
    cubo_presente = true;
    aux_pair = std::make_pair("cubo", Tupla3f(0.0f, 150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    tetraedro = new Tetraedro();
    aux.actualizar(negro, verde, azul);
    tetraedro->setMaterial(aux);
    tetraedro_presente = false;
    aux_pair = std::make_pair("tetraedro", Tupla3f(150.0f, 150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    ply = new ObjPLY("./plys/big_dodge.ply");
    aux.actualizar(negro, celeste, naranja);
    ply->setMaterial(aux);
    ply_presente = false;
    aux_pair = std::make_pair("ply", Tupla3f(-150.0f, -150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    swordfish_presente = true;
    swordfish = new Swordfish();
    aux_pair = std::make_pair("swordfish", Tupla3f(150.0f, 0.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    aux_pair = std::make_pair("lata", Tupla3f(-150.0f, 0.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    aux_pair = std::make_pair("esfera", Tupla3f(0.0f, -150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    aux_pair = std::make_pair("cono", Tupla3f(-150.0f, 150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    aux_pair = std::make_pair("cilindro", Tupla3f(150.0f, 150.0f, 0.0f));
    scene_arrangement.insert(aux_pair);

    lata_presente = true;
    cilindro_presente = false;
    cono_presente = true;
    esfera_presente = false;

    actualizar_revolucion = false;
    inicializarLuces();
    iluminacion_activa = true;
    texturas = true;

    Camara c1(0, Tupla3f(0.0f, 0.0f, 800.0f), Tupla3f(0.0f, 0.0f, 0.0f), Tupla3f(0.0f, 1.0f, 0.0f), 200, 200,
              Front_plane, Back_plane);
    camaras.push_back(c1);

    Camara c2(1, Tupla3f(0.0f, 0.0f, 800.0f), Tupla3f(0.0f, 0.0f, 0.0f), Tupla3f(0.0f, 1.0f, 0.0f), 200, 200,
              Front_plane, Back_plane);
    camaras.push_back(c2);

    Camara c3(0, Tupla3f(0.0f, 500.0f, 300.0f), Tupla3f(0.0f, 0.0f, 0.0f), Tupla3f(0.0f, 1.0f, 0.0f), 600, 200,
              Front_plane, Back_plane);
    camaras.push_back(c3);

    camara_activa = 0;
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
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    //Generamos la semilla para los rand utilizados
    srand(time(0));

    std::cout << "Bienvenido! Seleccione un menú" << std::endl <<
                 "\tO: Selección de objeto" << std::endl <<
                 "\tV: Selección de modo de visualización" << std::endl <<
                 "\tD: Selección de dibujado" << std::endl <<
                 "\tU: Tapas" << std::endl <<
                 "\tX: Selección de movimiento del M.J" << std::endl <<
                 "\tC: Menú de Cámara" << std::endl;
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar(bool color_coding_mode)
{
    modo_coloreado coloreado_old = coloreado;
    if (color_coding_mode)
        coloreado = COLOR_CODING;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    ejes.draw();

    if (texturas)
        glEnable(GL_TEXTURE_2D);
    if (iluminacion_activa)
        glEnable(GL_LIGHTING);

    for (unsigned i = 0; i < luces.size(); ++i){
        if (estado_luces[i+1])
            luces[i]->activar();
    }

    if (cubo_presente){
        if (texturas)
            cubo->activar_textura();

        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("cubo")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(1.0f, 1.0f, 0.2f);
            cubo->draw(visualizacion, estado_dibujados, coloreado, rojo_flat3);
        glPopMatrix();
    }

    if (tetraedro_presente){
        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("tetraedro")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            tetraedro->draw(visualizacion, estado_dibujados, coloreado, gris3);
        glPopMatrix();
    }

    if (ply_presente){
        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("ply")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(20.0,20.0,20.0);
            ply->draw(visualizacion, estado_dibujados, coloreado, verde3);
        glPopMatrix();
    }

    if (lata_presente){
        if (actualizar_revolucion || lata_cue == nullptr){
            lata_cue = new ObjRevolucion("lata-pcue.ply", 50, false, false, true);
            lata_bot = new ObjRevolucion("lata-pinf.ply", 50, false, true, false);
            lata_top = new ObjRevolucion("lata-psup.ply", 50, true, false, false, true);
            Material m1(negro, blanco, negro, 90.0);
            Material m2(negro, gris, blanco, 90.0);
            lata_cue->setMaterial(m1);
            lata_top->setMaterial(m2);
            lata_bot->setMaterial(m2);

            lata_cue->set_textura("text-lata-1.jpg");
        }

        if (texturas)
            lata_cue->activar_textura();
        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("lata")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(100.0,100.0,100.0);
            glRotatef(90.0f, 0, 1, 0);
            lata_cue->draw(visualizacion, estado_dibujados, coloreado, azul_flat3);
            glDisable(GL_TEXTURE_2D);
            lata_bot->draw(visualizacion, estado_dibujados, coloreado, azul_flat3);
            lata_top->draw(visualizacion, estado_dibujados, coloreado, azul_flat3);
            if (texturas)
                glEnable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    if (esfera_presente){
        if (actualizar_revolucion || esfera == nullptr){
            esfera = new Esfera(20, 200, 0.5, tapas);
            Material m3(negro, naranja, blanco, 90.0f);
            esfera->setMaterial(m3);
        }

        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("esfera")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(70.0,70.0,70.0);
            esfera->draw(visualizacion, estado_dibujados, coloreado, celeste3);
        glPopMatrix();
    }

    if (cono_presente){
        if (actualizar_revolucion || cono == nullptr){
            cono = new Cono(12, 50, 1, 0.35, tapas);
        }

        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("cono")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(70.0,70.0,70.0);
            glDisable(GL_TEXTURE_2D);
            cono->draw(visualizacion, estado_dibujados, coloreado, verde_flat3);
            if (texturas)
                glEnable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    if (cilindro_presente){
        if (actualizar_revolucion || cilindro == nullptr){
            cilindro = new Cilindro(12, 50, 1, 0.35, tapas);
        }

        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("cilindro")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            glScalef(70.0,70.0,70.0);
            cilindro->draw(visualizacion, estado_dibujados, coloreado, marron3);
        glPopMatrix();
    }

    if (swordfish_presente){
        glDisable(GL_TEXTURE_2D);
        glPushMatrix();
            Tupla3f pos = scene_arrangement.find("swordfish")->second;
            glTranslatef(pos(X), pos(Y), pos(Z));
            swordfish->draw(visualizacion, estado_dibujados, coloreado, naranja3);
        glPopMatrix();
        if (texturas)
            glEnable(GL_TEXTURE_2D);
    }

    actualizar_revolucion = false;

    if (color_coding_mode)
        coloreado = coloreado_old;
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
   //Para no inundar la pantalla con la misma tecla
   if (ultima_tecla != tecla){
        cout << "Tecla pulsada: '" << tecla << "'" << endl;
        ultima_tecla = tecla;
   }
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
                        "\tB: Activar Coche" << endl <<
                        "\tR: Activar ObjRevolucion" << endl <<
                        "\t3: Activar Esfera" << endl <<
                        "\t4: Activar Cono" << endl <<
                        "\t5: Activar Cilindro" << endl;
           modoMenu=SELOBJETO;
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

           // ESTAMOS EN MODO SELECCION DE DIBUJADO
       case 'D' :
            if (modoMenu == NADA){
               std::cout << "Modo selección de dibujado" << endl <<
                           "\t1: Modo directo" << endl <<
                           "\t2: Modo diferido" << endl;
               modoMenu=SELDIBUJADO;
            }
           break ;

       case 'X' :
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


           //Interruptores de las tapaderas
        case 'U':
           std::cout << "Modo selección de dibujado" << endl <<
                       "\tN: Tapa inferior" << endl <<
                       "\tM: Tapa superior" << endl;
           modoMenu = TAPAS;
           break;

       case 'C':
           modoMenu = CAMARA;
           break;
   }

   if (modoMenu == SELOBJETO){
       switch(toupper(tecla)){
       case 'C' :
              cubo_presente = !cubo_presente;
          break;

       case 'T' :
              tetraedro_presente = !tetraedro_presente;
          break;

       case 'B' :
               ply_presente = !ply_presente;
           break;

       case 'R':
              lata_presente = !lata_presente;
          break;

       case '3':
             esfera_presente = !esfera_presente;

         break;

       case '4':
            cono_presente = !cono_presente;

        break;

       case '5':
            cilindro_presente = !cilindro_presente;

        break;
       }
   }

   if (modoMenu == SELVISUALIZACION){
       switch(toupper(tecla)){
       case 'P':
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_POINT) != estado_dibujados.end())
                   estado_dibujados.erase(GL_POINT);

               else
                   estado_dibujados.insert(GL_POINT);


           break;
       case 'L':
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_LINE) != estado_dibujados.end())
                   estado_dibujados.erase(GL_LINE);

               else
                   estado_dibujados.insert(GL_LINE);

           break;
       case 'S':
               iluminacion_activa = false;
               glDisable(GL_LIGHTING);

               if (estado_dibujados.find(GL_FILL) != estado_dibujados.end() &&
                       coloreado != AJEDREZ)
                   estado_dibujados.erase(GL_FILL);

               else
                   estado_dibujados.insert(GL_FILL);

               coloreado = RELLENADO;

           break;
       case 'A':
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

           break;

        case 'I':
            std::cout << "Modo de iluminación" << endl <<
                        "\t0-7 Activar la luz i" << endl <<
                        "\tA: Modificar alpha" << endl <<
                        "\tB: Modificar beta" << endl <<
                        "\t>: Incrementar ángulo" << endl <<
                        "\t<: Reducir ángulo" << endl <<
                        "\tP: Animar luz puntual" << endl;
           iluminacion_activa = true;
           modoMenu = ILUMINACION;
           break;
       }
   }

   if (modoMenu == SELDIBUJADO){
       switch (toupper(tecla)) {
       case '1' :
               visualizacion = INMEDIATO;
           break;
       case '2' :
               visualizacion = VBO;
           break;
       }
   }

   if (modoMenu == TAPAS){
       switch (toupper(tecla)) {
       case 'M':
               tapas.first = !tapas.first;
               actualizar_revolucion = true;
          break;

       case 'N':
               tapas.second = !tapas.second;
               actualizar_revolucion = true;
          break;
       }
   }

   if (modoMenu == MOVIMIENTO){
       switch (toupper(tecla)) {
       case '3' :
               modoMenu = MOVIMIENTO_0;

           break;

      case '4' :
                  modoMenu = MOVIMIENTO_1;

              break;

      case '5' :
              modoMenu = MOVIMIENTO_2;

          break;

      case '6' :
              modoMenu = MOVIMIENTO_3;

          break;

      case '7' :
          if (modoMenu == MOVIMIENTO)
              modoMenu = MOVIMIENTO_AUTO;

          else if (modoMenu == MOVIMIENTO_AUTO)
              modoMenu = MOVIMIENTO;

          break;
       }
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
           if (rotaciones.first)
               static_cast<LuzDireccional*>(luces[1])->variarAnguloAlpha(0.5f);


           else if (rotaciones.second)
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(0.5f);

           break;

       case '<':
           if (rotaciones.first)
               static_cast<LuzDireccional*>(luces[1])->variarAnguloAlpha(-0.5f);


           else if (rotaciones.second)
               static_cast<LuzDireccional*>(luces[1])->variarAnguloBeta(-0.5f);

           break;

       case 'P':
            anima_luces = !anima_luces;
           break;
       }
   }

   if (modoMenu == CAMARA){
       if (tecla >= '0' && tecla <= '2'){
           camara_activa = tecla - '0';
           camaras[camara_activa].setProyeccion();
       }

       if (toupper(tecla) == 'G'){
           std::cout << "GODMODE" << std::endl;
           modoCamara = GODMODE;
       }
   }

   if (modoCamara == GODMODE){
       Tupla3f eyeAux = camaras[camara_activa].getEye();
       switch (toupper(tecla)) {
       case 'W':
           camaras[camara_activa].mover(eyeAux(X), eyeAux(Y), eyeAux(Z) - 10.0f);
           camaras[camara_activa].setAt(camaras[camara_activa].getEye() + Tupla3f(0.0f, 0.0f,-1.0f));
           break;
       case 'A':
           camaras[camara_activa].mover(eyeAux(X) - 10.0f, eyeAux(Y), eyeAux(Z));
           camaras[camara_activa].setAt(camaras[camara_activa].getEye() + Tupla3f(0.0f, 0.0f,-1.0f));
           break;

       case 'S':
           camaras[camara_activa].mover(eyeAux(X), eyeAux(Y), eyeAux(Z) + 10.0f);
           camaras[camara_activa].setAt(camaras[camara_activa].getEye() + Tupla3f(0.0f, 0.0f,-1.0f));
           break;

       case 'D':
           camaras[camara_activa].mover(eyeAux(X) + 10.0f, eyeAux(Y), eyeAux(Z));
           camaras[camara_activa].setAt(camaras[camara_activa].getEye() + Tupla3f(0.0f, 0.0f,-1.0f));
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
         camaras[camara_activa].rotarYExaminar(-0.001*(y-old_y));
         break;
       case GLUT_KEY_RIGHT:
         camaras[camara_activa].rotarYExaminar(0.001*(y-old_y));
         break;
       case GLUT_KEY_UP:
         camaras[camara_activa].rotarXExaminar(-0.001*(x-old_x));
         break;
       case GLUT_KEY_DOWN:
         camaras[camara_activa].rotarXExaminar(0.001*(x-old_x));
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
   camaras[camara_activa].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   for (unsigned i = 0; i < camaras.size(); ++i)
        camaras[i].setAspect(Height, Width);

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
   camaras[camara_activa].setObserver();
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
    Tupla3f pos(0.0f, -150.0f, 150.0f);
    estado_luces.assign(8, false);

    LuzPosicional *luz1 = new LuzPosicional(pos, GL_LIGHT1, negro, naranja, celeste);
    luces.push_back(luz1);

    LuzDireccional *luz2 = new LuzDireccional(Tupla2f(0.0, 0.0), GL_LIGHT2, negro, blanco, blanco);
    luces.push_back(luz2);
}

void Escena::animarIluminacion(){
    if (anima_luces){
        float max_range = 500.0f;
        float X_increment = rand()%20, Y_increment = rand()%20, Z_increment = rand()%20;
        Tupla4f current_pos = luces[0]->getPos();

        //La luz en la pos 0 es la puntual
        current_pos = luces[0]->getPos();

        if (current_pos(X) > max_range || current_pos(Y) > max_range){
            X_increment = -max_range;
            Y_increment = -max_range;
            Z_increment = -rand() % 1000;
        }

        luces[0]->setPos(X_increment, Y_increment, Z_increment);
    }
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

void Escena::clickRaton(int boton, int estado, int x, int y){
    old_x = x;
    old_y = y;

    if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN){
        if (camaras[camara_activa].getExaminando())
            modoCamara = EXAMINAR;

        else
            modoCamara = FP;
    }

    else if (boton == 3)
        camaras[camara_activa].zoom(0.8f);


    else if (boton == 4)
        camaras[camara_activa].zoom(1.2f);

    else if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        modo_coloreado coloreado_old = coloreado;
        coloreado = COLOR_CODING;

        dibuja_seleccion();
        processPick(x, y);
        coloreado = coloreado_old;
    }

    else
        modoCamara = ESTATICA;
}

void Escena::ratonMovido(int x, int y){
    if (modoCamara == EXAMINAR){
        camaras[camara_activa].rotarXExaminar(-0.005*(y-old_y));
        camaras[camara_activa].rotarYExaminar(0.005*(x-old_x));
        old_x = x;
        old_y = y;
    }

    if (modoCamara == FP){
        camaras[camara_activa].girar(x-old_x, y-old_y);
        old_x = x;
        old_y = y;
    }
}

void Escena::dibuja_seleccion(){
    std::pair<bool, bool> estadoAnterior(iluminacion_activa, texturas);
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    iluminacion_activa = false;
    glDisable(GL_TEXTURE);
    texturas = false;

    dibujar();
    //glutSwapBuffers();

    glEnable(GL_DITHER);
    if (estadoAnterior.first){
        glEnable(GL_LIGHTING);
        iluminacion_activa = true;
    }

    if (estadoAnterior.second){
        glEnable(GL_TEXTURE);
        texturas = true;
    }
}

void Escena::processPick(int x, int y){
    GLint viewport[4];
    GLubyte pixel[3];
    Malla3D* elegido;
    Material amarillo(Tupla4f(1.0f, 1.0f, 0.0f, 1.0f), Tupla4f(1.0f, 1.0f, 0.0f, 1.0f), Tupla4f(0.0f, 0.0f, 0.0f, 1.0f), 90.0f);

    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

    //restauro el color y material anteriores en caso de haber elegido algo antes
    if (!first_pick){
        if (old_color_material.first == lata_cue){
            lata_cue->setColor(old_color_material.second.first);
            lata_cue->setMaterial(old_color_material.second.second);
            lata_bot->setColor(old_color_material.second.first);
            lata_bot->setMaterial(old_color_material.second.second);
            lata_top->setColor(old_color_material.second.first);
            lata_top->setMaterial(old_color_material.second.second);
        }

        else if (swordfish_elegido){
            swordfish_elegido = false;
            swordfish->paint();
        }

        else if (old_color_material.first != nullptr){
            old_color_material.first->setColor(old_color_material.second.first);
            old_color_material.first->setMaterial(old_color_material.second.second);
        }
    }

    //Si se selecciona el vacío
    if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255 && camaras[camara_activa].getExaminando()){
        camaras[camara_activa].setExaminando(false);

        //No restaurar estado si se selecciona más de una vez el vacío
        if (elegido == nullptr)
            first_pick = true;

        elegido == nullptr;
    }

    else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0){
        elegido = cono;
        first_pick = false;

        old_color_material.first = cono;
        old_color_material.second = std::make_pair(cono->getColor(), cono->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("cono")->second);
        camaras[camara_activa].setExaminando(true);
        cono->setMaterial(amarillo);
        cono->setColor(amarillo3);
    }

    else if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0){
        elegido = cubo;
        first_pick = false;

        old_color_material.first = cubo;
        old_color_material.second = std::make_pair(cubo->getColor(), cubo->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("cubo")->second);
        camaras[camara_activa].setExaminando(true);
        cubo->setMaterial(amarillo);
        cubo->setColor(amarillo3);
    }

    else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255){
        elegido = lata_cue;
        first_pick = false;

        old_color_material.first = lata_cue;
        old_color_material.second = std::make_pair(lata_cue->getColor(), lata_cue->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("lata")->second);
        camaras[camara_activa].setExaminando(true);
        lata_cue->setMaterial(amarillo);
        lata_bot->setMaterial(amarillo);
        lata_top->setMaterial(amarillo);

        lata_cue->setColor(amarillo3);
        lata_bot->setColor(amarillo3);
        lata_top->setColor(amarillo3);
    }

    else if (pixel[0] == 255 && pixel[1] == 128 && pixel[2] == 0){
        swordfish_elegido = true;
        elegido == nullptr;
        first_pick = false;

        old_color_material.first = nullptr;
        camaras[camara_activa].setAt(scene_arrangement.find("swordfish")->second);
        camaras[camara_activa].setExaminando(true);
        swordfish->setMaterial(amarillo, amarillo);
        swordfish->setColor(amarillo3);
    }

    else if (pixel[0] == 178 && pixel[1] == 178 && pixel[2] == 178){
        elegido = tetraedro;
        first_pick = false;

        old_color_material.first = tetraedro;
        old_color_material.second = std::make_pair(tetraedro->getColor(), tetraedro->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("tetraedro")->second);
        camaras[camara_activa].setExaminando(true);
        tetraedro->setMaterial(amarillo);
        tetraedro->setColor(amarillo3);
    }

    else if (pixel[0] == 128 && pixel[1] == 0 && pixel[2] == 255){
        elegido = ply;
        first_pick = false;

        old_color_material.first = ply;
        old_color_material.second = std::make_pair(ply->getColor(), ply->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("ply")->second);
        camaras[camara_activa].setExaminando(true);
        ply->setMaterial(amarillo);
        ply->setColor(amarillo3);
    }

    else if (pixel[0] == 0 && pixel[1] == 204 && pixel[2] == 204){
        elegido = esfera;
        first_pick = false;

        old_color_material.first = esfera;
        old_color_material.second = std::make_pair(esfera->getColor(), esfera->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("esfera")->second);
        camaras[camara_activa].setExaminando(true);
        esfera->setMaterial(amarillo);
        esfera->setColor(amarillo3);
    }

    else if (pixel[0] == 76 && pixel[1] == 51 && pixel[2] == 0){
        elegido = cilindro;
        first_pick = false;

        old_color_material.first = cilindro;
        old_color_material.second = std::make_pair(cilindro->getColor(), cilindro->getMaterial());
        camaras[camara_activa].setAt(scene_arrangement.find("cilindro")->second);
        camaras[camara_activa].setExaminando(true);
        cilindro->setMaterial(amarillo);
        cilindro->setColor(amarillo3);
    }
}

Escena::~Escena(){
    for (unsigned i = 0; i < luces.size(); ++i)
        delete luces[i];
}
