
# include "so_model.h"

SoModel::SoModel()
 {
	 id = 0;
   _numpoints = 0;
   _phong = false;
   m = GsModel();
 }

void SoModel::init (char* Texturefile, GLuint _id)
 {
	 id = _id;
	loadTexture(Texturefile);
	// Load programs:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../mcol_gouraud.vert");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../gouraud.frag");
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
	_proggouraud.uniform_location(9, "Texture");

 }

void SoModel::loadTexture(char* textFile) {
	GsImage I = GsImage();

		//DOES NOT LOAD ANYTHING BUT PNG
		if (!I.load(textFile)) {
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

void SoModel::init()
{
	// Load programs:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../mcol_gouraud.vert");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../gouraud.frag");
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
	_proggouraud.uniform_location(9, "Texture");

}

static void printInfo(GsModel& m)
{
	std::cout << "V:  " << m.V.size() << "\n";
	std::cout << "F:  " << m.F.size() << "\n";
	std::cout << "N:  " << m.N.size() << "\n";
	std::cout << "M:  " << m.M.size() << "\n";
	std::cout << "Fn: " << m.Fn.size() << "\n";
	std::cout << "Fm: " << m.Fm.size() << "\n";
}

void SoModel::load(GsString fileName) {
	float f;
	GsString file;
	
	f = 0.005f; file = fileName;

	std::cout << "Loading " << file << "...\n";
	if (!m.load(file)) std::cout << "Error!\n";

	//printInfo(model);
	m.scale(f); // to fit our camera space
	build();
}



void SoModel::build()
{
	int i;

	//GsColor c;//No colors, only textures
	P.size(0); T.size(0); N.size(0);

	/* There are multiple ways to organize data to send to OpenGL.
	   Here we send material information per vertex but we only send the diffuse color
	   information per vertex. The other components are uniforms sent to affect the whole object.
	   This is a solution that keeps this code simple and is ok for most objects.
	*/

	// build arrays:
	int num;
	for (i = 0; i < m.F.size(); i++)
	{
		GsModel::Face& f = m.F[i];
		P.push() = m.V[f.a];
		P.push() = m.V[f.b];
		P.push() = m.V[f.c];

		if (m.Fn.size()>0 && i < m.Fn.size())
		{
			GsModel::Face& f = m.Fn[i];
			N.push() = m.N[f.a]; N.push() = m.N[f.b]; N.push() = m.N[f.c];
			//std::cout<<i<<": "<<N.top()<<"\n";
		}
		else if (m.N.size() > 0 && i < m.N.size())
		{
			GsVec n = m.N[i]; N.push() = n; N.push() = n; N.push() = n;
		}
		else
		{
			GsVec n = m.face_normal(i); N.push() = n; N.push() = n; N.push() = n;
		}

		//Pushing textures to model
//		T.push() = GsVec2((float)i / m.F.size(), 1.0f);
//		T.push() = GsVec2((float)i / m.F.size(), 0.0f);
//		T.push() = GsVec2((float)(i + 1) / m.F.size(), 0.0f);


		if (id==2) 
		{
			//std::cout << "THE BOX" << std::endl;
			T.push() = GsVec2(1.0f, 1.0f);
			T.push() = GsVec2(1.0f, 0.0f);
			T.push() = GsVec2(0.0f, 0.0f);
		}
		else
		{
			num = rand() % 2;
			//std::cout << num << std::endl;
			T.push() = GsVec2(num, num);
			T.push() = GsVec2(~num, num);
			T.push() = GsVec2(~num, ~num);
		}
		//NO COLORS
		//c = GsColor::gray;
		/*if ( m.Fm.size()>0 && i<m.Fm.size() )
		 { int id=m.Fm[i];
		   if (id<0) {
			   if (C.size()>0)c=C.top(); } else c=m.M[id].diffuse;
		   //std::cout<<i<<"/"<<id<<" "<<c<<"\n";
		 }
		else if ( m.M.size()>0 && i<m.M.size() )
		 { c = m.M[i].diffuse; }
		C.push()=c; C.push()=c; C.push()=c;*/
	  }

		if (m.M.size() > 0) _mtl = m.M[0]; else _mtl.init();

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

		//textures
		glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
		glBufferData(GL_ARRAY_BUFFER, T.size() * 2 * sizeof(float), &T[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0); // false means no normalization

		glBindVertexArray(0); // break the existing vertex array object binding.

		std::cout << "build ok.\n";

		// save size so that we can free our buffers and later draw the OpenGL arrays:
		_numpoints = P.size();

		// free non-needed memory:
		P.capacity(0); T.capacity(0); N.capacity(0);
}

void SoModel::draw( const GsMat& tr, const GsMat& pr, const GsLight& l){
   float f[4]; 
   float sh = (float)_mtl.shininess;
   if ( sh<0.001f ) sh=64;

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
   glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.specular.get(f));
   glUniform1fv(_proggouraud.uniloc[8], 1, &sh);

   glBindVertexArray ( va[0] );
   glDrawArrays ( GL_TRIANGLES, 0, _numpoints );
   glBindVertexArray(0); // break the existing vertex array object binding.
 }

void SoModel::drawShad(const GsMat& tr, const GsMat& pr, const GsLight& l) {
	float f[4];
	float sh = (float)_mtlsh.shininess;
	if (sh<0.001f) sh = 64;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(_proggouraud.id);
	glUniformMatrix4fv(_proggouraud.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_proggouraud.uniloc[1], 1, GL_FALSE, pr.e);
	glUniform3fv(_proggouraud.uniloc[2], 1, l.pos.e);

	glUniform4fv(_proggouraud.uniloc[3], 1, l.amb.get(f));
	glUniform4fv(_proggouraud.uniloc[4], 1, l.dif.get(f));
	glUniform4fv(_proggouraud.uniloc[5], 1, l.spe.get(f));

	float arr[4] = { 0.0f,0.0f,0.0f,0.0f };
	_mtlsh.ambient.set(arr);
	glUniform4fv(_proggouraud.uniloc[6], 1, _mtlsh.ambient.get(f));
	_mtlsh.specular.set(arr);
	glUniform4fv(_proggouraud.uniloc[7], 1, _mtlsh.specular.get(f));
	glUniform1fv(_proggouraud.uniloc[8], 1, &sh);

	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.
}