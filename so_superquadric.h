
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

#endif // SO_MODEL_H
