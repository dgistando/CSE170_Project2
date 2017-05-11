
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_light.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_model.h"
# include "so_texturedTube.h"
# include  "so_superquadric.h"

# include <vector>

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
  
	 ///////////////////////////////////////////

	 std::vector<zombie*> zombieList;
	 /////////////////////////////////////////////

	 time_t timer;

	 //AREYESCHANGESHIT
	 bool fireBool;
	 double startTime, initTime, currTime, timeDiff,
		 deltaZ, deltaY, theta, velocity, gravity, accelX;
	 GsMat bodyTransOLD, bodyRotOLD, translationsBackOLD, firstRotOLD, rotations2OLD, rotationsOLD, translationsOLD;
	 float gunMovxOLD;
	 /////////////////////////////////////////////

    // My scene objects:
    SoAxis _axis;
    SoModel _model, auto_gun,
					body,caps,
					gun,gun_base,left_antenna,
					right_antenna,wheels1,wheels2,wheels3,wheels4, wheels5,wheels6, crate, missle;


	SoTexturedTube ground, sky;

	float offset,wheelMov,capsMov,gunMovx,gunMovy,autoGunMovx,
		autoGunMovy,skyMov,X,Y,Z, camsh,camnod, antennaMov, bodyMovx, bodyMovy, bodyMovz, Bodyturn;
    // Scene data:
    bool  _viewaxis, camview__, turn;
    GsModel _gsm;
    GsLight _light;

	GLuint IDground, IDsky;
    
	std::vector<GLuint> ids;
    // App data:
    enum MenuEv { evOption0, evOption1 };
    float _rotx, _roty, _fovy, Ttheta, lookUp;
    int _w, _h, direction;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
    void loadModel ( int model );
    GsVec2 windowToScene ( const GsVec2& v );
	void loadGroundTexture(GLuint& id);

   private : // functions derived from the base class

    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
	//dgistandoo
	virtual void glutIdle();
	virtual void glutPassiveMouse(int x, int y);
 };

#endif // APP_WINDOW_H
