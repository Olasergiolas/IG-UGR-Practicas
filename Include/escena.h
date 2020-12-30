#ifndef _ESCENA_H
#define _ESCENA_H

#include "Include/ejes.h"
#include "Include/malla.h"
#include "Include/cubo.h"
#include "Include/tetraedro.h"
#include "set"
#include "Include/objply.h"
#include "Include/objrevolucion.h"
#include "Include/esfera.h"
#include "Include/cilindro.h"
#include "Include/cono.h"
#include "Include/luzposicional.h"
#include "Include/luzdireccional.h"
#include "Include/swordfish.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, TAPAS, ILUMINACION,
             MOVIMIENTO, MOVIMIENTO_0, MOVIMIENTO_1, MOVIMIENTO_2,
             MOVIMIENTO_3, MOVIMIENTO_AUTO} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   void clear_window();

   unsigned char ultima_tecla = ' ';
   unsigned gradoLibertad = 0;
   std::vector<Luz*> luces;
   std::vector<bool> estado_luces;
   menu modoMenu=NADA;
   modo_visualizacion visualizacion;
   modo_coloreado coloreado;
   std::set<GLenum> estado_dibujados;
   std::pair<bool, bool> tapas;
   std::pair<bool, bool> rotaciones;
   bool iluminacion_activa;
   bool actualizar_revolucion;
   // Objetos de la escena
   Ejes ejes;

   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   bool cubo_presente;

   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   bool tetraedro_presente;

   ObjPLY *ply = nullptr;
   bool ply_presente;
   bool cambiar_ply;

   ObjRevolucion *lata_cue = nullptr;
   bool lata_presente;

   ObjRevolucion *lata_top = nullptr;

   ObjRevolucion *lata_bot = nullptr;

   bool esfera_presente;
   Esfera *esfera = nullptr;

   bool cono_presente;
   Cono *cono = nullptr;

   bool cilindro_presente;
   Cilindro *cilindro = nullptr;

   bool swordfish_presente;
   Swordfish *swordfish = nullptr;

   bool anima_luces;

   public:

    Escena();
    ~Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    GLenum getIdLuz(unsigned char c);
    void inicializarLuces();
    void animarIluminacion();
    void animarModeloJerarquico();

};
#endif
