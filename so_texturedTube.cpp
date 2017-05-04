# include "so_texturedTube.h"

#define PI 3.14159265

SoTexturedTube::SoTexturedTube() {
	_numpoints = 0;
	_flatn = true;
	id = 0;
	I = GsImage();
}

void SoTexturedTube::init() {

	///////////////////
	//GsImage I;
//	gsuint id;

	/*
	//DOES NOT LOAD ANYTHING BUT PNG
	if (!I.load("../17161022_1140906752684459_1029165329_n.png")) {
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
	/////////////////
	*/

	// Load programs:
	//COULDNT LOAD THE OLD SHADER BECAUSE ASCII ERRORS
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../mcol_gouraud.vert");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../gouraud.frag");
	_proggouraud.init_and_link(_vshgou, _fshgou);

	//_vshphong.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_phong.glsl");
	//_fshphong.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_mcol_phong.glsl");
	//_progphong.init_and_link(_vshphong, _fshphong);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(3);       // will use 3 buffers

	_proggouraud.uniform_locations(11); // will send 10 variables
	_proggouraud.uniform_location(0, "vTransf");
	_proggouraud.uniform_location(1, "vProj");
	_proggouraud.uniform_location(2, "lPos");
	_proggouraud.uniform_location(3, "la");
	_proggouraud.uniform_location(4, "ld");
	_proggouraud.uniform_location(5, "ls");
	_proggouraud.uniform_location(6, "ka");
	_proggouraud.uniform_location(7, "ks");
	_proggouraud.uniform_location(8, "sh");
	_proggouraud.uniform_location(9, "Texture");
	_proggouraud.uniform_location(10, "shading");
}

void SoTexturedTube::build(bool back) {

	P.resize(0); N.resize(0); T.resize(0);

	GsVec a, b, c, d, e, f;
	GsVec n1, n2, n3, n4, n5, n6;

	if (back) {
		a = GsVec(-6.0f, 0.0f, 6.0f);
		b = GsVec(-6.0f, 0.0f, -6.0f);
		c = GsVec(6.0f, 0.0f, 6.0f);
		d = GsVec(6.0f, 0.0f, -6.0f);


		P.push_back(a);//top
		P.push_back(b);//bottom
		P.push_back(c);//topnext

		P.push_back(b);//bottom
		P.push_back(c);//topnext
		P.push_back(d);//bottomnext


		//Texture coordinates
		//NOT SURE ABOUT PUSHING BACK THE COORDINATES

		T.push_back(GsVec2(0.0f, 1.0f));
		T.push_back(GsVec2(0.0f, 0.0f));
		T.push_back(GsVec2(1.0f, 1.0f));

		T.push_back(GsVec2(1.0f, 1.0f));
		T.push_back(GsVec2(0.0f, 0.0f));
		T.push_back(GsVec2(0.0f, 1.0f));

		N.push_back(GsVec(0.0f, 1.0f, 0.0f));

	}
	else 
	{
		a = GsVec(-10.0f, 10.0f, -8.0f);
		b = GsVec(-10.0f, -10.0f, -8.0f);
		c = GsVec(10.0f, 10.0f, -8.0f);
		d = GsVec(10.0f, -10.0f, -8.0f);

		P.push_back(a);//top
		P.push_back(b);//bottom
		P.push_back(c);//topnext

		P.push_back(c);//bottom
		P.push_back(b);//topnext
		P.push_back(d);//bottomnext

		T.push_back(GsVec2(1.0f, 0.0f));
		T.push_back(GsVec2(0.0f, 0.0f));
		T.push_back(GsVec2(1.0f, 1.0f));

		T.push_back(GsVec2(1.0f, 1.0f));
		T.push_back(GsVec2(0.0f, 0.0f));
		T.push_back(GsVec2(1.0f, 0.0f));



		N.push_back(GsVec(0.0f, 1.0f, 0.0f));
	}

	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 8; // increase specular effect

	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*P.size(), &P[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), &N[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//textures
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
	P.clear();  N.clear(); T.clear();
	// (leave NL untouched because it will be used by another class for display)

}

void SoTexturedTube::draw(const GsMat& tr, const GsMat& pr, const GsLight& l, const GLuint& id ,float shading) {
	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);

		glUseProgram(_proggouraud.id);
		glUniformMatrix4fv(_proggouraud.uniloc[0], 1, GL_FALSE, tr.e);
		glUniformMatrix4fv(_proggouraud.uniloc[1], 1, GL_FALSE, pr.e);
		glUniform3fv(_proggouraud.uniloc[2], 1, l.pos.e);

		glUniform4fv(_proggouraud.uniloc[3], 1, l.amb.get(f));
		glUniform4fv(_proggouraud.uniloc[4], 1, l.dif.get(f));
		glUniform4fv(_proggouraud.uniloc[5], 1, l.spe.get(f));

		glUniform4fv(_proggouraud.uniloc[6], 1, _mtl.ambient.get(f));
		//glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.diffuse.get(f));
		glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.specular.get(f));

		glUniform1fv(_proggouraud.uniloc[8], 1, &sh);
		//glUniform1i(_proggouraud.uniloc[9], 0);
		glUniform1f(_proggouraud.uniloc[10], shading);

	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.
}