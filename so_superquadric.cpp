#define _USE_MATH_DEFINES
# include <math.h>
# include "so_superquadric.h"

double bodyheight, bodywidth, bodylength;
SoSuperquadric::SoSuperquadric()
{
	_numpoints = 0;
}

void SoSuperquadric::init(int t)
{
	// Load programs:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_gouraud.glsl");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_gouraud.glsl");
	_proggouraud.init_and_link(_vshgou, _fshgou);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(3);       // will use 3 buffers

	_proggouraud.uniform_locations(10); // will send 9 variables
	_proggouraud.uniform_location(0, "vTransf");
	_proggouraud.uniform_location(1, "vProj");
	_proggouraud.uniform_location(2, "lPos");
	_proggouraud.uniform_location(3, "la");
	_proggouraud.uniform_location(4, "ld");
	_proggouraud.uniform_location(5, "ls");
	_proggouraud.uniform_location(6, "ka");
	_proggouraud.uniform_location(7, "ks");
	_proggouraud.uniform_location(8, "sh");
	_proggouraud.uniform_location(9, "shader");
	
	if (t == 1) {//body
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/body.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 2) {//head
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/head.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 3) {//arm
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/arms.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 4) {//arm
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/arms.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 5) {//leg
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/legs.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 6) {//leg
		GsImage I;
		gsuint id;
		if (!I.load("../textures/HumanTex/legs.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(6); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} /*else if(t == 7) {//floor
		GsImage I;
		gsuint id;
		if (!I.load("../grass.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(1); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 8) {//wall1
		GsImage I;
		gsuint id;
		if (!I.load("../walls.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(1); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 9) {//wall2
		GsImage I;
		gsuint id;
		if (!I.load("../walls.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(1); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	} else if (t == 10) {//wall3
		GsImage I;
		gsuint id;
		if (!I.load("../walls.png")) { std::cout << "COULD NOT LOAD IMAGE!\n"; exit(1); }
		glGenTextures(1, &_texid); // generated ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		I.init(0, 0);
	}*/

	type = t;
}

static float sgn(float x) { return x<0 ? -1.0f : x>0 ? 1.0f : 0; }
static float cf(float w, float m) { float cw = (float)cos(w); return sgn(cw)*pow(GS_ABS(cw), m); }
static float sf(float w, float m) { float sw = (float)sin(w); return sgn(sw)*pow(GS_ABS(sw), m); }

//See formula in https://en.wikipedia.org/wiki/Superquadrics
static GsPnt evaluate(float u, float v, float *p)
{
	const float w = 2.0f;
	float r = p[0]; float s = p[1]; float t = p[2]; float A = p[3]; float B = p[4]; float C = p[5];
	return GsPnt(
		A * cf(v, w / r) * cf(u, w / r),
		B * cf(v, w / s) * sf(u, w / s),
		C * sf(v, w / t)
		);
}

static GsVec estnormal(float u, float v, float* p, float inc)
{
	// here we estimate the tangent plane with three points around (u,v)
	// and use the plane normal as the normal at point (u,v)
	return normal(
		evaluate(u - inc, v - inc, p),
		evaluate(u + inc, v - inc, p),
		evaluate(u, v + inc, p));
}

void SoSuperquadric::build( float len, float wt, float ht) {

	//height is Y axis, width is X axis and width is Z axis
	length = len;	//x
	width = wt;		//z
	height = ht;		//y
	// build arrays:

	P.size(0); T.size(0); N.size(0); NL.size(0);
	GsVec n1, n2, n3, n4;
	GsVec a, b, c, d, e, f, g, h;
	float c1, c2, c3, c4;
	switch (type) {
	case 1: //body
		bodyheight = height;
		bodywidth = width;
		bodylength = length;

		//all 8 vertexes needed to make all the faces of the body
		a = GsVec((float)-(length / 2), (float)height, (float)(width / 2));
		b = GsVec((float)(length / 2), (float)height, (float)(width / 2));
		c = GsVec((float)-(length / 2), (float)0.0f, (float)(width / 2));
		d = GsVec((float)(length / 2), (float)0.0f, (float)(width / 2));
		e = GsVec((float)-(length / 2), (float)height, (float)-(width / 2));
		f = GsVec((float)(length / 2), (float)height, (float)-(width / 2));
		g = GsVec((float)-(length / 2), (float)0.0f, (float)-(width / 2));
		h = GsVec((float)(length / 2), (float)0.0f, (float)-(width / 2));

		//P pushback in order of ABCD, BFDH, FEHG, EAGC, EFAB, CDGH faces for the rectangle
		//order of triangle push backs is left to right, then the solo point
		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.83f, 0.75f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.00f); T.push() = GsVec2(0.83f, 0.00f); T.push() = GsVec2(0.83f, 0.75f);
		T.push() = GsVec2(0.0f, 0.75f); T.push() = GsVec2(0.16f, 0.75f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.16f, 0.0f); T.push() = GsVec2(0.16f, 0.75f);
		T.push() = GsVec2(0.16f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.16f, 0.0f); T.push() = GsVec2(0.16f, 0.00f); T.push() = GsVec2(0.5f, 0.00f); T.push() = GsVec2(0.5f, 0.75f);
		T.push() = GsVec2(0.83f, 0.75f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.83f, 0.00f); T.push() = GsVec2(0.83f, 0.00f); T.push() = GsVec2(1.0f, 0.00f); T.push() = GsVec2(1.00f, 0.83f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.83f, 1.0f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.83f, 0.75f); T.push() = GsVec2(0.83f, 1.0f);
		T.push() = GsVec2(0.16f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.16f, 0.75f); T.push() = GsVec2(0.16f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 1.0f);
		break;
	case 2: //head
		a = GsVec((float)-(length / 2), (float)(height + bodyheight), (float)(width / 2));
		b = GsVec((float)(length / 2), (float)(height + bodyheight), (float)(width / 2));
		c = GsVec((float)-(length / 2), (float)(0.0f + bodyheight), (float)(width / 2));
		d = GsVec((float)(length / 2), (float)(0.0f + bodyheight), (float)(width / 2));
		e = GsVec((float)-(length / 2), (float)(height + bodyheight), (float)-(width / 2));
		f = GsVec((float)(length / 2), (float)(height + bodyheight), (float)-(width / 2));
		g = GsVec((float)-(length / 2), (float)(0.0f + bodyheight), (float)-(width / 2));
		h = GsVec((float)(length / 2), (float)(0.0f + bodyheight), (float)-(width / 2));

		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.5f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.5f);
		T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(1.0f, 0.5f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(1.0f, 0.0f); T.push() = GsVec2(1.0f, 0.5f);
		T.push() = GsVec2(0.0f, 0.5f); T.push() = GsVec2(0.25f, 0.5f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.25f, 0.00f); T.push() = GsVec2(0.25f, 0.5f);
		T.push() = GsVec2(0.25f, 0.5f); T.push() = GsVec2(0.5f, 0.5f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.5f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.75f, 1.0f); T.push() = GsVec2(0.5f, 0.5f); T.push() = GsVec2(0.5f, 0.5f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.75f, 1.0f);
		T.push() = GsVec2(0.25f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.25f, 0.5f); T.push() = GsVec2(0.25f, 0.5f); T.push() = GsVec2(0.5f, 0.5f); T.push() = GsVec2(0.5f, 1.0f);

		break;
	case 3: //right arm
			//all 8 vertexes needed to make all the faces of the body
		a = GsVec((float)(-(length / 2) + (3 * bodylength / 4)), (float)-height, (float)(width / 2));
		b = GsVec((float)((length / 2) + (3 * bodylength / 4)), (float)-height, (float)(width / 2));
		c = GsVec((float)(-(length / 2) + (3 * bodylength / 4)), (float)0.0f, (float)(width / 2));
		d = GsVec((float)((length / 2) + (3 * bodylength / 4)), (float)0.0f, (float)(width / 2));
		e = GsVec((float)(-(length / 2) + (3 * bodylength / 4)), (float)-height, (float)-(width / 2));
		f = GsVec((float)((length / 2) + (3 * bodylength / 4)), (float)-height, (float)-(width / 2));
		g = GsVec((float)(-(length / 2) + (3 * bodylength / 4)), (float)0.0f, (float)-(width / 2));
		h = GsVec((float)((length / 2) + (3 * bodylength / 4)), (float)0.0f, (float)-(width / 2));

		//P pushback in order of ABCD, BFDH, FEHG, EAGC, EFAB, CDGH faces for the rectangle
		//order of triangle push backs is left to right, then the solo point
		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.75f);	T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.5f, 0.0f);
		T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(1.0f, 0.0f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.0f);
		T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.25f, 0.00f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.0f);
		T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.0f);
		T.push() = GsVec2(0.25f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 1.0f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.75f, 1.0f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.75f, 1.0f);

		break;
	case 4: //left arm
			//all 8 vertexes needed to make all the faces of the body
		a = GsVec((float)(-(length / 2) - (3 * bodylength / 4)), (float)-height, (float)(width / 2));
		b = GsVec((float)((length / 2) - (3 * bodylength / 4)), (float)-height, (float)(width / 2));
		c = GsVec((float)(-(length / 2) - (3 * bodylength / 4)), (float) 0.0f, (float)(width / 2));
		d = GsVec((float)((length / 2) - (3 * bodylength / 4)), (float) 0.0f, (float)(width / 2));
		e = GsVec((float)(-(length / 2) - (3 * bodylength / 4)), (float)-height, (float)-(width / 2));
		f = GsVec((float)((length / 2) - (3 * bodylength / 4)), (float)-height, (float)-(width / 2));
		g = GsVec((float)(-(length / 2) - (3 * bodylength / 4)), (float)0.0f, (float)-(width / 2));
		h = GsVec((float)((length / 2) - (3 * bodylength / 4)), (float) 0.0f, (float)-(width / 2));

		//P pushback in order of ABCD, BFDH, FEHG, EAGC, EFAB, CDGH faces for the rectangle
		//order of triangle push backs is left to right, then the solo point
		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.75f);	T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.5f, 0.0f);
		T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(1.0f, 0.0f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.0f);
		T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.25f, 0.00f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.0f);
		T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.0f);
		T.push() = GsVec2(0.25f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 1.0f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.75f, 1.0f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.75f, 1.0f);

		break;
	case 5: //right leg
		a = GsVec((float)(-(length / 2) + bodylength / 4), (float)(height - bodyheight), (float)(width / 2));
		b = GsVec((float)((length / 2) + bodylength / 4), (float)(height - bodyheight), (float)(width / 2));
		c = GsVec((float)(-(length / 2) + bodylength / 4), (float)(0.0f - bodyheight), (float)(width / 2));
		d = GsVec((float)((length / 2) + bodylength / 4), (float)(0.0f - bodyheight), (float)(width / 2));
		e = GsVec((float)(-(length / 2) + bodylength / 4), (float)(height - bodyheight), (float)-(width / 2));
		f = GsVec((float)((length / 2) + bodylength / 4), (float)(height - bodyheight), (float)-(width / 2));
		g = GsVec((float)(-(length / 2) + bodylength / 4), (float)(0.0f - bodyheight), (float)-(width / 2));
		h = GsVec((float)((length / 2) + bodylength / 4), (float)(0.0f - bodyheight), (float)-(width / 2));

		//P pushback in order of ABCD, BFDH, FEHG, EAGC, EFAB, CDGH faces for the rectangle
		//order of triangle push backs is left to right, then the solo point
		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.75f);
		T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(1.0f, 0.0f); T.push() = GsVec2(1.0f, 0.75f);
		T.push() = GsVec2(0.0f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.25f, 0.00f); T.push() = GsVec2(0.25f, 0.75f);
		T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.75f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.75f, 1.0f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.75f, 1.0f);
		T.push() = GsVec2(0.25f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 1.0f);

		break;
	case 6: //left leg
		a = GsVec((float)(-(length / 2) - bodylength / 4), (float)(height - bodyheight), (float)(width / 2));
		b = GsVec((float)((length / 2) - bodylength / 4), (float)(height - bodyheight), (float)(width / 2));
		c = GsVec((float)(-(length / 2) - bodylength / 4), (float)(0.0f - bodyheight), (float)(width / 2));
		d = GsVec((float)((length / 2) - bodylength / 4), (float)(0.0f - bodyheight), (float)(width / 2));
		e = GsVec((float)(-(length / 2) - bodylength / 4), (float)(height - bodyheight), (float)-(width / 2));
		f = GsVec((float)((length / 2) - bodylength / 4), (float)(height - bodyheight), (float)-(width / 2));
		g = GsVec((float)(-(length / 2) - bodylength / 4), (float)(0.0f - bodyheight), (float)-(width / 2));
		h = GsVec((float)((length / 2) - bodylength / 4), (float)(0.0f - bodyheight), (float)-(width / 2));

		//P pushback in order of ABCD, BFDH, FEHG, EAGC, EFAB, CDGH faces for the rectangle
		//order of triangle push backs is left to right, then the solo point
		P.push() = a; P.push() = b; P.push() = c; P.push() = c; P.push() = d; P.push() = b; //front
		P.push() = b; P.push() = f; P.push() = d; P.push() = d; P.push() = h; P.push() = f; //left
		P.push() = f; P.push() = e; P.push() = h; P.push() = h; P.push() = g; P.push() = e; //back
		P.push() = e; P.push() = a; P.push() = g; P.push() = g; P.push() = c; P.push() = a; //right
		P.push() = e; P.push() = f; P.push() = a; P.push() = a; P.push() = b; P.push() = f; //top
		P.push() = c; P.push() = d; P.push() = g; P.push() = g; P.push() = h; P.push() = d; //bottom

		T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.75f);
		T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(1.0f, 0.75f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(0.75f, 0.0f); T.push() = GsVec2(1.0f, 0.0f); T.push() = GsVec2(1.0f, 0.75f);
		T.push() = GsVec2(0.0f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.0f, 0.0f); T.push() = GsVec2(0.25f, 0.00f); T.push() = GsVec2(0.25f, 0.75f);
		T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.25f, 0.0f); T.push() = GsVec2(0.5f, 0.0f); T.push() = GsVec2(0.5f, 0.75f);
		T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.75f, 1.0f); T.push() = GsVec2(0.75f, 0.5f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.75f, 0.75f); T.push() = GsVec2(0.75f, 1.0f);
		T.push() = GsVec2(0.25f, 1.0f); T.push() = GsVec2(0.5f, 1.0f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.25f, 0.75f); T.push() = GsVec2(0.5f, 0.75f); T.push() = GsVec2(0.5f, 1.0f);

		break;
	/*case 7: //floor
		a = GsVec(  5.0f, -1.0f,  5.0f);
		b = GsVec(  5.0f, -1.0f, -5.0f);
		c = GsVec( -5.0f, -1.0f,  5.0f);
		d = GsVec( -5.0f, -1.0f, -5.0f);

		P.push() = a; P.push() = b; P.push() = c;
		P.push() = c; P.push() = d; P.push() = b;

		T.push() = GsVec2(0, 1); T.push() = GsVec2(1, 1); T.push() = GsVec2(0, 0);
		T.push() = GsVec2(0, 0); T.push() = GsVec2(1, 0); T.push() = GsVec2(1, 1);

		break;
	case 8: //wall 1
		a = GsVec(-5.0f, 5.0f,  5.0f);
		b = GsVec(-5.0f, 5.0f, -5.0f);
		c = GsVec(-5.0f, -1.0f,  5.0f);
		d = GsVec(-5.0f, -1.0f, -5.0f);

		P.push() = a; P.push() = b; P.push() = c;
		P.push() = c; P.push() = d; P.push() = b;

		T.push() = GsVec2(1, 0); T.push() = GsVec2(0, 0); T.push() = GsVec2(1, 1);
		T.push() = GsVec2(1, 1); T.push() = GsVec2(0, 1); T.push() = GsVec2(0, 0);

		break;
	case 9: //wall 2
		a = GsVec(-5.0f, 5.0f, -5.0f);
		b = GsVec( 5.0f, 5.0f, -5.0f);
		c = GsVec(-5.0f, -1.0f, -5.0f);
		d = GsVec( 5.0f, -1.0f, -5.0f);

		P.push() = a; P.push() = b; P.push() = c;
		P.push() = c; P.push() = d; P.push() = b;

		T.push() = GsVec2(1, 0); T.push() = GsVec2(0, 0); T.push() = GsVec2(1, 1);
		T.push() = GsVec2(1, 1); T.push() = GsVec2(0, 1); T.push() = GsVec2(0, 0);

		break;
	case 10: //wall 3
		a = GsVec( 5.0f, 5.0f, -5.0f);
		b = GsVec( 5.0f, 5.0f, 5.0f);
		c = GsVec( 5.0f, -1.0f, -5.0f);
		d = GsVec( 5.0f, -1.0f, 5.0f);

		P.push() = a; P.push() = b; P.push() = c;
		P.push() = c; P.push() = d; P.push() = b;

		T.push() = GsVec2(1, 0); T.push() = GsVec2(0, 0); T.push() = GsVec2(1, 1);
		T.push() = GsVec2(1, 1); T.push() = GsVec2(0, 1); T.push() = GsVec2(0, 0);

		break;
		*/
		default:break;
	}
	
/*
	for (double i = 0; i < 2*pi; i += angle) {

		GsVec a = GsVec(radiusBot*cos(i + angle), -length, radiusBot*sin(i + angle));
		GsVec b = GsVec(radiusTop*cos(i), length, radiusTop*sin(i));
		GsVec c = GsVec(radiusTop*cos(i + angle), length, radiusTop*sin(i + angle));
		P.push() = a; P.push() = b; P.push() = c;

		GsVec d = GsVec(radiusBot*cos(i + angle), -length, radiusBot*sin(i + angle));
		GsVec e = GsVec(radiusTop*cos(i), length, radiusTop*sin(i));
		GsVec f = GsVec(radiusBot*cos(i), -length, radiusBot*sin(i));
		P.push() = f; P.push() = e; P.push() = d;

		//Top and bottom circles
		GsVec m = GsVec(radiusBot*cos(i), -length, radiusBot*sin(i));
		GsVec n = GsVec(radiusBot*cos(i + angle), -length, radiusBot*sin(i + angle));
		GsVec o = GsVec(0.0, -length, 0.0);
		P.push() = m; P.push() = n; P.push() = o;

		GsVec j = GsVec(radiusTop*cos(i), length, radiusTop*sin(i));
		GsVec k = GsVec(radiusTop*cos(i + angle), length, radiusTop*sin(i + angle));
		GsVec l = GsVec(0.0, length, 0.0);
		P.push() = l; P.push() = k; P.push() = j;

		float T1 = i/(2*pi);
		float T2 = (i+angle)/(2*pi);

		T.push() = GsVec2(T2, 1); T.push() = GsVec2(T1, 0); T.push() = GsVec2(T2, 0);
		T.push() = GsVec2(T1, 1); T.push() = GsVec2(T1, 0); T.push() = GsVec2(T2, 1);
		T.push() = GsVec2(0, 0); T.push() = GsVec2(0, 0); T.push() = GsVec2(0, 0);
		T.push() = GsVec2(0, 0); T.push() = GsVec2(0, 0); T.push() = GsVec2(0, 0);

		n1 = a - o; //n1 *= -1;
		n2 = b - l; //n2 *= -1;
		n3 = f - o; //n3 *= -1;
		n4 = c - l; //n4 *= -1;
		GsVec n5 = GsVec(0.0, -1.0, 0.0);
		GsVec n6 = GsVec(0.0, 1.0, 0.0);
		N.push() = n1; N.push() = n2; N.push() = n4;
		N.push() = n3; N.push() = n2; N.push() = n1;
		N.push() = n5; N.push() = n5; N.push() = n5;
		N.push() = n6; N.push() = n6; N.push() = n6;

		
	}*/

	//T.size(P.size()); T.setall(GsColor::red);

	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 0; // increase specular effect

						// send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*P.size(), P.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), N.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
	glBufferData(GL_ARRAY_BUFFER, T.size() * 2 * sizeof(float), &T[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0); // false means no normalization

	glBindVertexArray(0); // break the existing vertex array object binding.

						  // save size so that we can free our buffers and later draw the OpenGL arrays:
	_numpoints = P.size();

	// on first build only print number of triangles to keep an eye on the overall resolution:
	static bool firstbuild = true;
	if (firstbuild) { std::cout << "\nNum triangles in superquadric: " << _numpoints / 3.0f << "\n\n"; firstbuild = false; }

	// free non-needed memory:
	P.capacity(0); T.capacity(0); N.capacity(0);
	// (leave NL untouched because it will be used by another class for display)
}

void SoSuperquadric::draw(const GsMat& tr, const GsMat& pr, const GsLight& l)
{
	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;

	glUseProgram(_proggouraud.id);
	glUniformMatrix4fv(_proggouraud.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_proggouraud.uniloc[1], 1, GL_FALSE, pr.e);
	glUniform3fv(_proggouraud.uniloc[2], 1, l.pos.e);
	glUniform4fv(_proggouraud.uniloc[3], 1, l.amb.get(f));
	glUniform4fv(_proggouraud.uniloc[4], 1, l.dif.get(f));
	glUniform4fv(_proggouraud.uniloc[5], 1, l.spe.get(f));
	glUniform4fv(_proggouraud.uniloc[6], 1, _mtl.ambient.get(f));
	glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.specular.get(f));
	glUniform1fv(_proggouraud.uniloc[8], 1, &sh);
	glUniform1f(_proggouraud.uniloc[9], shader);

	glBindTexture(GL_TEXTURE_2D, _texid);
	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.
}

