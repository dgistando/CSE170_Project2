
# include <iostream>
# include <gsim/gs.h>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   initPrograms ();
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   _viewaxis = true;
   camview__ = false;
   _fovy = GS_TORAD(60.0f);
   _rotx = _roty = 0;
   _w = w;
   _h = h;
   offset = 0.2f;
   camsh = 0.0f;
   camnod = 0.0f;

	wheelMov = 0.0f;
	capsMov = 0.0f;

	gunMovx = 0.0f;
	gunMovy = 0.0f;

	autoGunMovx = 0.0f;
	autoGunMovy = 0.0f;
	skyMov = 0.0f;

	antennaMov = 0.0f;
	bodyMovx = 0.0f;
	bodyMovy = 0.0f;
	bodyMovz = 0.0f;
	Bodyturn = 0.0f;

	direction = 0;

   IDground = 45;
   IDsky = 35;
   loadGroundTexture(IDsky);
   loadGroundTexture(IDground);

   turn = false;

   X = 0.0f;
   Y = 0.0f;
   Z = 0.0f;
   //////////////////////////////////////////
   moveX = 0.0;
   moveZ = 0.0;
   camChange = true;
   BT = 0.0f;
   HT = 0.0f;
   RAT = 0.0f;
   LAT = 0.0f;
   RLT = 0.0f;
   LLT = 0.0f;

   scale = -1.0f;
 }

void AppWindow::initPrograms ()
 {
   // Init my scene objects:
	 //you can initialize with a texture as location of image in itit
   _axis.init ();
   ground.init();
   sky.init();

   //Initialize model objects
   auto_gun.init("../textures/hoof.png",1);
   body.init("../textures/black-metal-plate-armour-texture-rivets-grunge-as-background-31353987.png",1);
   caps.init("../textures/hoof.png",1);
   gun.init("../textures/hoof.png",1);
   gun_base.init("../textures/hoof.png",1);
   left_antenna.init("../textures/hoof.png", 1);
   right_antenna.init("../textures/hoof.png",1);
   wheels1.init("../textures/hoof.png", 1);
   wheels2.init("../textures/hoof.png", 1);
   wheels3.init("../textures/hoof.png", 1);
   wheels4.init("../textures/hoof.png", 1);
   wheels5.init("../textures/hoof.png", 1);
   wheels6.init("../textures/hoof.png", 1);

   crate.init("../textures/crate_1.png",2);

   // set light:
   //_light.set ( GsVec(0,0,10), GsColor(90,90,90,255), GsColor::white, GsColor::white );
   _light.set ( GsVec(0,1,1), GsColor::gray, GsColor::gray, GsColor::gray );

   // Load demo model:
   auto_gun.load("../models/Ozelot/auto_gun.obj");
   body.load("../models/Ozelot/body.obj");
   caps.load("../models/Ozelot/caps.obj");
   gun.load("../models/Ozelot/gun.obj");
   gun_base.load("../models/Ozelot/gun_base.obj");
   left_antenna.load("../models/Ozelot/left_antenna.obj");
   right_antenna.load("../models/Ozelot/right_antenna.obj");
   wheels1.load("../models/Ozelot/wheels1.obj");
   wheels2.load("../models/Ozelot/wheels2.obj");
   wheels3.load("../models/Ozelot/wheels3.obj");
   wheels4.load("../models/Ozelot/wheels4.obj");
   wheels5.load("../models/Ozelot/wheels5.obj");
   wheels6.load("../models/Ozelot/wheels6.obj");

   crate.load("../models/Crate1.obj");

   ground.build(1);
   sky.build(0);


   /////////////////////////////
   humanBody.init(1); //body
   head.init(2);	//head
   RtArm.init(3);	//right arm
   LfArm.init(4);	//left arm
   RtLeg.init(5);	//right leg
   LfLeg.init(6);	//left leg

   humanBody.build(2 * scale, scale, 3 * scale);
   head.build(2 * scale, 2 * scale, 2 * scale);
   RtArm.build(scale, scale, 3 * scale);
   LfArm.build(scale, scale, 3 * scale);
   RtLeg.build(scale, scale, 3 * scale);
   LfLeg.build(scale, scale, 3 * scale);



   redraw();
 }


void AppWindow::loadGroundTexture(GLuint& id) {
	GsImage I;

		//DOES NOT LOAD ANYTHING BUT PNG
		if ((id == 45) ? !I.load("../textures/13037682-White-marble-texture-High-resolution-Stock-Photo.png") : !I.load("../textures/sky_107.png")) {
			std::cout << "COULD NOT LOAD IMAGE!!!\n";

			exit(5);
		}

		glGenTextures(1, &id); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0); // free image from CPU 
}

static void printInfo ( GsModel& m )
 {
   std::cout<<"V:  "<<m.V.size()<<"\n";
   std::cout<<"F:  "<<m.F.size()<<"\n";
   std::cout<<"N:  "<<m.N.size()<<"\n";
   std::cout<<"M:  "<<m.M.size()<<"\n";
   std::cout<<"Fn: "<<m.Fn.size()<<"\n";
   std::cout<<"Fm: "<<m.Fm.size()<<"\n";
 }
void AppWindow::loadModel ( int model )//call rebuild after this function.
 {
   /*float f;
   GsString file;
   switch ( model )
    { case 1: f=0.01f; file="../models/porsche.obj"; break;
      case 2: f=0.20f; file="../models/al.obj"; break;
      case 3: f=0.10f; file="../models/f-16.obj"; break;
	  case 4: f = 0.05f; file = "../models/Ozelot23.obj"; break;
	  case 5: f = 0.05f; file = "../models/alpaca_leg_wt.obj"; break;
      default: return;
    }
   std::cout<<"Loading "<<file<<"...\n";
   if ( !_gsm.load ( file ) ) std::cout<<"Error!\n";
   printInfo ( _gsm );
   _gsm.scale ( f ); // to fit our camera space
   _model.build(_gsm);*/
   redraw();
 }

// mouse events are in window coordinates, but your 2D scene is in [0,1]x[0,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene ( const GsVec2& v )
 {
   // GsVec2 is a lighteweight class suitable to return by value:
   return GsVec2 ( (2.0f*(v.x/float(_w))) - 1.0f,
                    1.0f - (2.0f*(v.y/float(_h))) );
 }

// Called every time there is a window event
void AppWindow::glutKeyboard ( unsigned char key, int x, int y )
 {
	 bool rd = true;

   switch ( key )
    { 
     case 'b': _viewaxis = !_viewaxis;redraw(); break;
	  case ' ': camview__ = !camview__; camsh = 0.0f; camnod = 0.0f; rd = false; break;
	  case 27 : exit(1); // Esc was pressed

	  case 'i':offset += 0.04f; break;
	  case 'k':offset -= 0.04f; std::cout << offset << std::endl; break;

	  case 'p':camnod += 0.04f; break;
	  case ';':camnod -= 0.04f; std::cout << camnod << std::endl; break;
	  case 'l':camsh -= 0.04f; break;
	  case 39:camsh += 0.04f; std::cout << camsh << std::endl; break;

	  case 'a':gunMovy -= 0.04f; std::cout << gunMovx << std::endl; break;
	  case 's':gunMovx += 0.04f; std::cout << gunMovy << std::endl; break;
	  case 'w':gunMovx -= 0.04f; break;
	  case 'd':gunMovy += 0.04f; break;

	  case 'A':autoGunMovy -= 0.04f; std::cout << autoGunMovx << std::endl; break;
	  case 'S':capsMov -= 0.04f; std::cout << autoGunMovy << std::endl; break;
      case 'W':capsMov += 0.04f; break;
	  case 'D':autoGunMovy += 0.04f; break;
	


	  case 'r':antennaMov += 0.04f; break;
	  case 'f':antennaMov -= 0.04f; /*std::cout << antennaMov << std::endl;*/ break;

	  case 'x': X -= 0.01f; std::cout <<"x-: " <<X << std::endl; break;
	  case 'X': X += 0.01f; std::cout <<"x+: "<<X << std::endl; break;
	  case 'y': Y -= 0.01f; std::cout <<"y-: "<<Y << std::endl; break;
	  case 'Y': Y += 0.01f; std::cout <<"y+: "<< Y << std::endl; break;
	  case 'z': Z -= 0.01f; std::cout <<"z-: "<<Z << std::endl; break;
	  case 'Z': Z += 0.01f; std::cout <<"Z+: "<<Z << std::endl; break;
	  
      default : 
                break;
	}
   if(rd)redraw();
 }

void AppWindow::glutSpecial ( int key, int x, int y )
 {
   bool rd=true;
   const float incr=GS_TORAD(2.5f);
   const float incf=0.05f;

   if (camview__) {
	   _rotx = 0.0f;
	   _roty = 0.0f;

	   switch (key)
	   {
	   case GLUT_KEY_LEFT: Bodyturn += (float)(GS_PI / 2);   direction++; turn = true;  break;
	   case GLUT_KEY_RIGHT:  Bodyturn += (float)(3*GS_PI / 2);  direction+=3; turn = true; break;
	   case GLUT_KEY_UP:

		   switch (abs(direction))
		   {
		   case 0:bodyMovx += 0.0f; bodyMovy += 0.0f; bodyMovz += 0.2f; break;
		   case 1:bodyMovx += 0.2f; bodyMovy += 0.0f; bodyMovz += 0.0f; break;
		   case 2:bodyMovx += 0.0f; bodyMovy += 0.0f; bodyMovz -= 0.2f; break;
		   case 3:bodyMovx -= 0.2f; bodyMovy += 0.0f; bodyMovz += 0.0f; break;
		   default:break;
		   }
		   wheelMov += 0.1f;
		   turn = false;
		   break;
	   case GLUT_KEY_DOWN: 

		   switch (abs(direction))
		   {
		   case 0:bodyMovx -= 0.0f; bodyMovy -= 0.0f; bodyMovz -= 0.2f; break;
		   case 1:bodyMovx -= 0.2f; bodyMovy -= 0.0f; bodyMovz -= 0.0f; break;
		   case 2:bodyMovx -= 0.0f; bodyMovy -= 0.0f; bodyMovz += 0.2f; break;
		   case 3:bodyMovx += 0.2f; bodyMovy -= 0.0f; bodyMovz -= 0.0f; break;
		   default:break;
		   }
		   wheelMov -= 0.1f;
		   turn = false;
		   break;
	   case GLUT_KEY_PAGE_UP:   _fovy -= incf; turn = false; break;
	   case GLUT_KEY_PAGE_DOWN: _fovy += incf; turn = false; break;
	   default: return; // return without rendering
	   }
	   direction = direction % 4;
	}
   else 
   {
	   turn = false;
	   switch (key)
	   {//0.04444f
	   case GLUT_KEY_LEFT:      _roty -= incr; skyMov += 0.0444f; break;
	   case GLUT_KEY_RIGHT:     _roty += incr; skyMov -= 0.0444f; break;
		case GLUT_KEY_UP:		 _rotx += incr; break;
		case GLUT_KEY_DOWN:		  _rotx -= incr;break;
		case GLUT_KEY_PAGE_UP:   _fovy -= incf; break;
		case GLUT_KEY_PAGE_DOWN: _fovy += incf; break;
	   default: return; // return without rendering
	   }

   }
   if (rd) redraw(); // ask the window to be rendered when possible
 }

void AppWindow::glutMouse ( int b, int s, int x, int y )
 {
   // The mouse is not used in this example.
   // Recall that a mouse click in the screen corresponds
   // to a whole line traversing the 3D scene.
 }

void AppWindow::glutMotion ( int x, int y )
 {
 }

void AppWindow::glutMenu ( int m )
 {
   std::cout<<"Menu Event: "<<m<<std::endl;
 }

void AppWindow::glutReshape ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::glutDisplay()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Build a cross with some lines (if not built yet):
	if (_axis.changed) // needs update
	{
		_axis.build(1.0f); // axis has radius 1.0
	}

	// Define our scene transformation:
	GsMat rx, ry, stransf;
	rx.rotx(_rotx);
	ry.roty(_roty);
	stransf = rx*ry; // set the scene transformation matrix

	// Define our projection transformation:
	// (see demo program in gltutors-projection.7z, we are replicating the same behavior here)
	GsMat camview, persp, sproj;

	float grownd[4] = { 0.0f,0.5f,0.0f,-0.001f };
	float light[4] = { 0.9f, 0.9f, 0.9f, 0.2f };

	float dot = grownd[0] * light[0] +
		grownd[1] * light[1] +
		grownd[2] * light[2] +
		grownd[3] * light[3];

	GsMat shadProj(
		dot - light[0] * grownd[0],
		0.0f - light[0] * grownd[1],
		0.0f - light[0] * grownd[2],
		0.0f - light[0] * grownd[3],
		0.0f - light[1] * grownd[0],
		dot - light[1] * grownd[1],
		0.0f - light[1] * grownd[2],
		(0.0f - light[1] * grownd[3]),
		0.0f - light[2] * grownd[0],
		0.0f - light[2] * grownd[1],
		dot - light[2] * grownd[2],
		0.0f - light[2] * grownd[3],
		0.0f - light[3] * grownd[0],
		0.0f - light[3] * grownd[1],
		0.0f - light[3] * grownd[2],
		dot - light[3] * grownd[3]
		);


	//std::cout << "camview" << std::endl;
	if (!camview__) {
		GsVec eye(0, 2, 3), center(camsh, camnod, 0), up(0, 1, 0);
		camview.lookat(eye, center, up); // set our 4x4 "camera" matrix
	}
	else
	{
		GsVec eye(0, 2, 3), center(bodyMovx, 0 , bodyMovz), up(0, 1, 0);
		camview.lookat(eye, center, up); // set our 4x4 "camera" matrix
	}

   float aspect=1.0f, znear=0.1f, zfar=50.0f;
   persp.perspective ( _fovy, aspect, znear, zfar ); // set our 4x4 perspective matrix

   GsMat translations, rotations, rotations2, translationsBack;
   //translations.translation(-0.28f, -0.4f, -0.72f);//left Antenna to center
   //translations.translation(0.28f, -0.4f, -0.72f);//right Antenna to center

   GsMat Lantenna,Rantenna;


   // Our matrices are in "line-major" format, so vertices should be multiplied on the 
   // right side of a matrix multiplication, therefore in the expression below camview will
   // affect the vertex before persp, because v' = (persp*camview)*v = (persp)*(camview*v).
   sproj = persp * camview; // set final scene projection

   //  Note however that when the shader receives a matrix it will store it in column-major 
   //  format, what will cause our values to be transposed, and we will then have in our 
   //  shaders vectors on the left side of a multiplication to a matrix.


   // Draw:
   if ( _viewaxis ) _axis.draw (stransf, sproj);
   
   GsMat bodyTrans, bodyRot;

   bodyRot.roty(Bodyturn);
   bodyTrans.translation(bodyMovx, bodyMovy, bodyMovz);//back

   body.draw(stransf*bodyTrans*bodyRot, sproj, _light);
   body.drawShad(stransf*shadProj*bodyTrans*bodyRot, sproj, _light);



   //AUTO GUN ROTATION
   translations.translation(0.04f, -0.66f, -0.02f);//autogun to center
   rotations.roty(autoGunMovy);
   translationsBack.translation(-0.04f, 0.66f, 0.02f);
   auto_gun.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   auto_gun.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   //CAPS ROTATION
   translations.translation(0.0f, -0.62f, 0.34f);//caps to center
   rotations.rotx(capsMov);
   translationsBack.translation(0.0f, 0.62f, -0.34f);
   caps.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   caps.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   //GUN ROTATION
   translations.translation(-0.02f, -0.88f, 0.58f);//gun to center
   rotations.rotx(gunMovx);
   rotations2.roty(gunMovy);
   translationsBack.translation(0.02f, 0.88f, -0.58f);
   gun.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations, sproj, _light);

   gun.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations, sproj, _light);

   //GUN BASE ROTATION
   translations.translation(-0.02f, -0.76f, 0.6f);//left Antenna to center
   rotations.roty(gunMovy);
   translationsBack.translation(0.02f, 0.76f, -0.6f);
   gun_base.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   gun_base.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   
   //ROTATION FOR LEFT ANTENNA
   translations.translation(-0.28f, -0.4f, -0.72f);//move left to center
   rotations.rotx(antennaMov);//rotate
   translationsBack.translation(0.28f, 0.4f, 0.72f);//move back
   left_antenna.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   left_antenna.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   //ROTATION FOR RIGHT ANTENNA
   translations.translation(0.28f, -0.4f, -0.72f);
   rotations.rotx(antennaMov);
   translationsBack.translation(-0.28f, 0.4f, 0.72f);//move back
   right_antenna.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   right_antenna.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   

   translations.translation(0.0f, -0.23f, -0.775f);//1
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.23f, 0.775f);//1
   wheels1.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels1.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   translations.translation(0.0f, -0.11f, -0.59f);//2
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.11f, 0.59f);//2
   wheels2.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels2.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   translations.translation(0.0f, -0.11f, -0.335f);//3
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.11f, 0.335f);//3
   wheels3.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels3.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   translations.translation(0.0f, -0.11f, -0.1f);//4
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.11f, 0.1f);//4
   wheels4.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels4.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   translations.translation(0.0f , -0.11f, 0.125f);//5
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.11f, -0.125f);//5
   wheels5.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels5.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);

   translations.translation(0.0f, -0.13f, 0.335f);//6
   rotations.rotx(wheelMov);
   translationsBack.translation(0.0f, 0.13f, -0.335f);//6
   wheels6.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);
   wheels6.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations*translations, sproj, _light);


   std::cout << "moveValex: " << bodyMovx <<" "<<direction<< std::endl;
   std::cout << "moveValey: " << bodyMovy << std::endl;
   std::cout << "moveValez: " << bodyMovz << std::endl;
   
   

   ground.draw(stransf, sproj, _light, IDground, 0.75f);
   rotations.roty(skyMov);
   sky.draw(stransf*rotations, sproj, _light, IDsky, 0.02f);


   GsMat Scale;
   Scale.scale(2);
   translations.translation(2.5f, 0.12f, 0.0f);
   crate.draw(stransf*Scale*translations, sproj, _light);

   //////////////////////////////////////////////////////////////////////

   GsMat rotB( //rotations of the body, unused
	   cos(BT), 0.0f, -sin(BT), 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f,
	   sin(BT), 0.0f, cos(BT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat rotH( //rotations of the head
	   cos(HT), 0.0f, -sin(HT), 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f,
	   sin(HT), 0.0f, cos(HT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat rotRA( //rotations of the right arm
	   1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, cos(RAT), -sin(RAT), 0.0f,
	   0.0f, sin(RAT), cos(RAT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat rotLA( //rotations of the left arm
	   1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, cos(LAT), -sin(LAT), 0.0f,
	   0.0f, sin(LAT), cos(LAT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat rotLL( //rotations of the left leg
	   1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, cos(LLT), -sin(LLT), 0.0f,
	   0.0f, sin(LLT), cos(LLT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat rotRL( //rotations of the right leg
	   1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, cos(RLT), -sin(RLT), 0.0f,
	   0.0f, sin(RLT), cos(RLT), 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat moveArmOrigin(
	   1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, -3 * scale,
	   0.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat moveArmBack;
   moveArmBack.translation(0, 0.35f, 0);

   GsMat move(
	   1.0f, 0.0f, 0.0f, moveX,
	   0.0f, 1.0f, 0.0f, (3 * scale - 1),
	   0.0f, 0.0f, 1.0f, moveZ,
	   0.0f, 0.0f, 0.0f, 1.0f
   );
   GsMat test = moveArmOrigin * rotRA;

   if (_viewaxis) _axis.draw(stransf, sproj);

   GsMat scale1;
   scale1.scale(.0000000003f);

   GsMat reflect(
	   -1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, -1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f
   );

   translations.translation(0,0.4f,0);

   //main body
   humanBody.draw(stransf * translations * scale1 * move * reflect, sproj, _light);
   head.draw(stransf * translations * scale1* move * rotH* reflect, sproj, _light);

   //RtArm.draw(stransf * scale1* move * moveArmBack * rotRA* reflect, sproj, _light); //old
  // LfArm.draw(stransf * scale1* move * moveArmBack * rotLA* reflect, sproj, _light); //old

   LfArm.draw(stransf * translations * moveArmBack * scale1* move * moveArmBack * rotLA* reflect, sproj, _light);
   RtArm.draw(stransf * translations * moveArmBack * scale1* move * rotRA * reflect, sproj, _light);
   RtLeg.draw(stransf * translations * scale1* move * rotRL* reflect, sproj, _light);
   LfLeg.draw(stransf * translations * scale1* move * rotLL* reflect, sproj, _light);

   /*
   //shadow
   float groundx = 0.0f;
   float groundy = 1.0f;
   float groundz = 0.0f;
   float groundw = 1.0f;
  // float dot = (lightx * groundx) + (lighty * groundy) + (lightz * groundz) + (lightw * groundw);

   GsMat shadow(
	   dot - lightx*groundx, 0.0f - lightx*groundy, 0.0f - lightx*groundz, 0.0f - lightx*groundw,
	   0.0f - lighty*groundx, dot - lighty*groundy, 0.0f - lighty*groundz, 0.0f - lighty*groundw,
	   0.0f - lightz*groundx, 0.0f - lightz*groundy, dot - lightz*groundz, 0.0f - lightz*groundw,
	   0.0f - lightw*groundx, 0.0f - lightw*groundy, 0.0f - lightw*groundz, dot - lightw*groundw
   );

   glMultMatrixf((const GLfloat*)shadow);
   shadow = stransf*shadow;
   humanBody.draw(shadow  * move, sproj, _light);
   head.draw(shadow  * move * rotH, sproj, _light);
   RtArm.draw(shadow  * move * moveArmBack * rotRA, sproj, _light);
   LfArm.draw(shadow  * move * moveArmBack * rotLA, sproj, _light);
   RtLeg.draw(shadow  * move * rotRL, sproj, _light);
   LfLeg.draw(shadow  * move * rotLL, sproj, _light);
   */

   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}


