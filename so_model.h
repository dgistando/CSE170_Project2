
// Ensure the header file is included only once in multi-file projects
#ifndef SO_MODEL_H
#define SO_MODEL_H

// Include needed header files
# include <gsim/gs_mat.h>
# include <gsim/gs_light.h>
# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_model.h>
# include <gsim/gs.h>
# include "ogl_tools.h"

# include <gsimage/gs_image.h>

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class SoModel : public GlObjects
 { private :
    GlShader _vshgou, _fshgou;
    GlProgram _proggouraud;
	GsModel m;

    GsArray<GsVec>   P; // coordinates
  //  GsArray<GsColor> C; // diffuse colors per face
	GsArray<GsVec2> T;
    GsArray<GsVec>   N; // normals
	GLuint id;

    GsMaterial _mtl, _mtlsh;    // main material
    int _numpoints;     // just saves the number of points
    bool _phong;
   public :
    SoModel ();
    void phong ( bool b ) { _phong=b; }
    bool phong () const { return _phong; }
	void init();
	void loadTexture(char* text);
	void init(char* p, GLuint id);
	void load(GsString fileName);
    void build ();
    void draw ( const GsMat& tr, const GsMat& pr, const GsLight& l);
	void drawShad(const GsMat& tr, const GsMat& pr, const GsLight& l);

 };

#endif // SO_MODEL_H
