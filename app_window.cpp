
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
   _rotx = 0;
   _roty = 0;
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
	lookUp = 0.0f;

	antennaMov = 0.0f;
	bodyMovx = 0.0f;
	bodyMovy = 0.0f;
	bodyMovz = 0.0f;
	Bodyturn = 0.0f;

	Ttheta = 0.0f;
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

   //AREYESCHANGESHIT
   startTime = gs_time();
   velocity = 0.5;
   accelX = 0.00;
   gravity = -0.25;
   initTime = 0.00;
   currTime = 0.00;
   timeDiff = 0.00;
   fireBool = FALSE;
   deltaY = 0.00;
   deltaZ = 0.00;
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

   missle.init("../textures/crate_1.png", 2);

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

   missle.load("../models/missle.obj");

   ground.build(1);
   sky.build(0);


   /////////////////////////////
 //  zombieList = std::vector<zombie*>();

   zombieList.push_back(new zombie());

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
	  case ' ': camview__ = !camview__; 
		  camsh = 0.0f;
		  camnod = 0.0f;
		  rd = false;
		  _rotx = 0.0f;
		  _roty = 0.0f;
		  break;
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
	  
		  // AREYESEDITSHIT
		  // new app window controls
	  case '9': if (fireBool == FALSE)
	  {
		  fireBool = 1; initTime = gs_time(); std::cout << "!!! ~~~ A BUTTON WAS PRESSED ~~~ !!!" << std::endl;  break;
	  }
	  case '0': std::cout << "timeDiff since start up:\t" << timeDiff << " | fire:\t" << fireBool
		  << " | deltaY , deltaZ:\t" << deltaY << " , " << deltaZ << " | gunMovsin:\t" << sin(gunMovx) << std::endl;  break;

	  case '1': velocity -= .04; std::cout << "velocity:\t" << velocity << std::endl;  break;
	  case '2': velocity += .04; std::cout << "velocity:\t" << velocity << std::endl;  break;
	  case '3': accelX -= .04; std::cout << "accelX:\t" << accelX << std::endl;  break;
	  case '4': accelX += .04; std::cout << "accelX:\t" << accelX << std::endl;  break;
	  case '5': gravity -= .04; std::cout << "gravity:\t" << gravity << std::endl;  break;
	  case '6': gravity += .04; std::cout << "gravity:\t" << gravity << std::endl;  break;


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
	

	   switch (key)
	   {
		   //case GLUT_KEY_LEFT: Bodyturn += (float)(GS_PI / 2);   direction++; turn = true;  break;
		   //case GLUT_KEY_RIGHT:  Bodyturn += (float)(3*GS_PI / 2);  direction+=3; turn = true; break;
		case GLUT_KEY_LEFT: Ttheta += ((float)(GS_PI / 2)/12);   direction++; turn = true;  break;
		case GLUT_KEY_RIGHT:  Ttheta -= ((float)(GS_PI / 2)/12);  direction+=3; turn = true; break;
		case GLUT_KEY_UP:
			bodyMovz += cos(Ttheta)*0.08f;
			bodyMovx += sin(Ttheta)*0.08f;

		   wheelMov += 0.1f;
		   turn = false;
		   break;
	   case GLUT_KEY_DOWN: 

		   bodyMovz -= cos(Ttheta)*0.08f;
		   bodyMovx -= sin(Ttheta)*0.08f;

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

void AppWindow::glutPassiveMouse(int x, int y)
{
	//std::cout << "glut PASSIVE Motion x: " << x <<"window size: w"<< _w << std::endl;
	//std::cout << "glut PASSIVE Motion y: " << y << std::endl;

	//get distance from the center
	int distanceFromCenter = abs(x - (_w / 2));

	//the further you are from the center the faster the faster you turn
	if (distanceFromCenter > (_w / 30)) {
		_roty = (x > (_w / 2)) ? _roty + (float)(distanceFromCenter / (_w*4.7f)) : _roty - (float)(distanceFromCenter / (_w*4.7f));
	}

	lookUp = -((float)(y / (_h*1.0f))) + 1.5f;
	redraw();
}

void AppWindow::glutIdle()
{
	if (fireBool == TRUE)
		redraw();

	if ((deltaY < -1.00) && (timeDiff < 1000))
	{
		fireBool = 0;
		std::cout << "FIRE BOOL CHANGED TO 0!" << std::endl;
		redraw();
	}

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
	GsMat camTrans, camTransback;
	camTrans.translation(bodyMovx, bodyMovy, (bodyMovz-0.5));
	camTransback.translation(-bodyMovx, -bodyMovy,-(bodyMovz-0.5));
	rx.rotx(_rotx);
	ry.roty(_roty);
	stransf = rx*camTrans*ry*camTransback; // set the scene transformation matrix

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
		GsVec 
			eye(bodyMovx+0.1f ,1.4f ,bodyMovz-1),
			center(bodyMovx, lookUp+0.5f , bodyMovz),
			up(0, 1, 0);
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
   
   GsMat bodyTrans, bodyRot, missleTrans, missleScale, missleFireTrans, missleMat;

   bodyRot.roty(Ttheta);
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
   GsMat firstRot;
   firstRot.roty(-(_roty + GS_PI) - Ttheta);

   rotations.rotx(gunMovx);
   rotations2.roty(gunMovy);
   translationsBack.translation(0.02f, 0.88f, -0.58f);
   gun.draw(stransf*bodyTrans*bodyRot*translationsBack*firstRot*rotations2*rotations*translations, sproj, _light);

   gun.drawShad(stransf*shadProj*bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations, sproj, _light);

   // AREYESEDITSHIT
   //DRAW MISSLE IN THE SAME PLACE AS THE GUN plus some trans mat to factor in diff in center of model
   missleTrans.translation(-0.2f, 1.0f, -1.15f);
   missleScale.scale(0.5f);

   if (fireBool == TRUE)
   {
	   currTime = gs_time();
	   timeDiff = currTime - initTime;

	   deltaZ = (velocity*cos(-gunMovx)*timeDiff) + (.5 *accelX*(pow(timeDiff, 2)));
	   deltaY = (velocity*sin(-gunMovx)*timeDiff) + (.5 *gravity*(pow(timeDiff, 2)));
	   missleFireTrans.translation(0.0f, float(deltaY), float(deltaZ));

	   missle.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations*missleFireTrans*missleTrans*missleScale, sproj, _light);

   }
   else
   {
	   missleMat = bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations*missleTrans*missleScale;
	   missle.draw(stransf*bodyTrans*bodyRot*translationsBack*rotations2*rotations*translations*missleTrans*missleScale, sproj, _light);
	   deltaY = 0.00;
	   deltaZ = 0.00;
   }

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
   zombieList[0]->drawZombie(stransf, sproj, _light);


   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}


