// Ensure the header file is included only once in multi-file projects
#ifndef SO_QUAD_H
#define SO_QUAD_H

// Include needed header files
# include <gsim/gs_mat.h>
# include <gsim/gs_light.h>
# include <gsim/gs_color.h>
# include <gsim/gs_material.h>
# include <gsim/gs_array.h>
# include <gsim/gs_image.h>
# include <vector>
# include "ogl_tools.h"

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class SoSuperquadric : public GlObjects
 { private :
    GlShader _vshgou, _fshgou, _vshphong, _fshphong;
    GlProgram _proggouraud, _progphong;
    GsArray<GsVec>   P; // coordinates
    GsArray<GsVec2>  T; // diffuse colors per face
    GsArray<GsVec>   N; // normals
    GsMaterial _mtl;


	GLuint _texid, _texid2;
    int _numpoints;     // just saves the number of points

   public :
    GsArray<GsVec> NL; // normal lines computed in last build

	float length;
	float width;
	float height;
	float bodyL;
	float bodyW;
	float bodyH;

	int type;//type determines what body part it is

	float shader = 0.75;



   public :
    SoSuperquadric ();
    void init (int type);
	  void build( float len, float w, float h);
    void draw ( const GsMat& tr, const GsMat& pr, const GsLight& l );
 };

class zombie
{
public:

  SoSuperquadric body;
  SoSuperquadric head;
  SoSuperquadric LeftArm;
  SoSuperquadric RightArm;
  SoSuperquadric LeftLeg;
  SoSuperquadric RightLeg;

  GsMat currentLocation;
  std::vector<GsMat> locations;

  zombie() {

    body.init(1);
    head.init(2);
    LeftArm.init(3);
    RightArm.init(4);
    LeftLeg.init(5);
    RightLeg.init(6);

    //two spawn locations
    int ran = rand()%2;
    if(ran == 0) {
      currentLocation =
      (
   	   1.0f, 0.0f, 0.0f, 5.0f,
   	   0.0f, 1.0f, 0.0f, 0.0f,
   	   0.0f, 0.0f, 1.0f, 5.0f,
   	   0.0f, 0.0f, 0.0f, 1.0f
      );
    } else {
      currentLocation =
      (
   	   1.0f, 0.0f, 0.0f, -5.0f,
   	   0.0f, 1.0f, 0.0f, 0.0f,
   	   0.0f, 0.0f, 1.0f, -5.0f,
   	   0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    float scale = 0.01;

    body.build(2* scale, 1* scale, 3* scale);
    head.build(2* scale, 2* scale, 2* scale);
    LeftArm.build(1* scale, 1* scale, 3* scale);
    RightArm.build(1* scale, 1* scale, 3* scale);
    LeftLeg.build(1* scale, 1* scale, 3* scale);
    RightLeg.build(1* scale, 1* scale, 3* scale);
  }

  void drawZombie(const GsMat& stransf, const GsMat& sproj, const GsLight& _light) {
	  body.draw(stransf*currentLocation, sproj, _light);
	  head.draw(stransf*currentLocation, sproj, _light);
	  LeftArm.draw(stransf*currentLocation, sproj, _light);
	  RightArm.draw(stransf*currentLocation, sproj, _light);
	  LeftLeg.draw(stransf*currentLocation, sproj, _light);
	  RightLeg.draw(stransf*currentLocation, sproj, _light);
  }
/*
  int factorial(int i) {
  	if (i == 1 || i == 0) return 1;
  	return (i + factorial(i - 1));
  }

  float binomialCoefficient( float n, float i) {
  	return ( factorial(n) / ( factorial(i) * factorial(n - i) ));
  }

  GsVec eval_bezier(float t, const GsArray<GsVec>& points) {

  	GsVec location;
  	location.x = 0;
  	location.z = 0;
  	int N = points.size();

  	for (int i = 0; i < N; i++) {

  		location.x = location.x + (binomialCoefficient((float)(N - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (N - 1 - i)) * points[i].x);
  		location.z = location.z + (binomialCoefficient((float)(N - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (N - 1 - i)) * points[i].z);

  	}

  	return location;
  }

  void pathing(GsMat TankLocation) {

    bezier.V.capacity(0);
    const GsArray<GsVec>& V = _poly.vertexarray();
    int c = 0;
    for (float i = 0; i <= t; i++) {

      GsVec P = eval_bezier((float)(i / t), V);
      bezier.add(P, c);
      c++;
    }

  }
*/
  ~zombie() {}


};

#endif
