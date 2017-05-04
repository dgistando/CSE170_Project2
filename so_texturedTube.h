#pragma once
#ifndef SO_TEXTUREDTUBE
#define SO_TEXTUREDTUBE

# include <gsim/gs_mat.h>
# include <gsim/gs_light.h>
# include <gsim/gs_color.h>
# include <gsim/gs_material.h>
# include <gsim/gs_array.h>
# include "ogl_tools.h"

# include <vector> 
# include <gsim/gs_image.h>

class SoTexturedTube : public GlObjects
{
private:
	GlShader _vshgou, _fshgou, _vshphong, _fshphong;
	GlProgram _proggouraud, _progphong;

	gsuint id;
	GsImage I;

	std::vector<GsVec> P;
	std::vector<GsVec> N;
	std::vector<GsVec2> T;

	//GsArray<GsVec>   P; // coordinates
	//GsArray<GsColor> C; // diffuse colors per face
	//GsArray<GsVec>   N; // normals

	GsMaterial _mtl;
	int _numpoints;     // just saves the number of points
	bool _flatn;

public:
	GsArray<GsVec> NL; // normal lines computed in last build
public:
	SoTexturedTube();
	void init();
	void flat(bool b) { _flatn = b; }
	void build(bool);
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l, const GLuint&, float shading);
};

#endif