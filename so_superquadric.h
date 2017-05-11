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
# include "math.h"

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class SoSuperquadric : public GlObjects
{
private:
	GlShader _vshgou, _fshgou, _vshphong, _fshphong;
	GlProgram _proggouraud, _progphong;
	GsArray<GsVec>   P; // coordinates
	GsArray<GsVec2>  T; // diffuse colors per face
	GsArray<GsVec>   N; // normals
	GsMaterial _mtl;


	GLuint _texid, _texid2;
	int _numpoints;     // just saves the number of points

public:
	GsArray<GsVec> NL; // normal lines computed in last build

	float length;
	float width;
	float height;
	float bodyL;
	float bodyW;
	float bodyH;

	int type;//type determines what body part it is

	float shader = 0.75;



public:
	SoSuperquadric();
	void init(int type);
	void build(float len, float w, float h);
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);
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
	std::vector<GsVec> locations;

	float AT = -(GS_PI / 2);
	GsMat ArmOuts = 
		GsMat( //rotations of the right arm
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(AT), -sin(AT), 0.0f,
		0.0f, sin(AT), cos(AT), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	GsMat ArmUp =
		GsMat( //rotations of the right arm
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.125f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	float scale = 0.05;
	GsMat TransUp =
		GsMat(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 3 * scale,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

		zombie() {

			body.init(1);
			head.init(2);
			LeftArm.init(3);
			RightArm.init(4);
			LeftLeg.init(5);
			RightLeg.init(6);

			//two spawn locations
			int ran = rand() % 2;
			if (ran == 0) {
				currentLocation =
					GsMat(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
						);
			}
			else {
				currentLocation =
					GsMat(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
						);
			}

			body.build(2 * scale, 1 * scale, 3 * scale);
			head.build(2 * scale, 2 * scale, 2 * scale);
			LeftArm.build(1 * scale, 1 * scale, 3 * scale);
			RightArm.build(1 * scale, 1 * scale, 3 * scale);
			LeftLeg.build(1 * scale, 1 * scale, 3 * scale);
			RightLeg.build(1 * scale, 1 * scale, 3 * scale);
		}

		void drawZombie(const GsMat& stransf, const GsMat& sproj, const GsLight& _light) {
			body.draw(stransf*currentLocation, sproj, _light);
			head.draw(stransf*currentLocation, sproj, _light);
			LeftArm.draw(stransf*currentLocation*ArmOuts*ArmUp, sproj, _light);
			RightArm.draw(stransf*currentLocation*ArmOuts*ArmUp, sproj, _light);
			LeftLeg.draw(stransf*currentLocation, sproj, _light);
			RightLeg.draw(stransf*currentLocation, sproj, _light);
		}


		int factorial(int i) {
			if (i == 1 || i == 0) return 1;
			return (i + factorial(i - 1));
		}

		float binomialCoefficient(float n, float i) {
			return (factorial(n) / (factorial(i) * factorial(n - i)));
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

		void pathing(GsVec TankLocation) {

			//delets all elements in locations
			locations.clear();

			GsArray<GsVec> V;

			V.push()= (currentLocation);

			//stores locations and fins distance
			int N = 3;
			int Cx = 0;// = currentLocation.x;
			int Cz = 0;// = currentLocation.z;
			int Tx = TankLocation.x;
			int Tz = TankLocation.z;

			int distance = sqrt((Tx - Cx)*(Tx - Cx) + (Tz - Cz)*(Tz - Cz));
			int increment = distance / (N + 1);
			//adds in N random control points between current and tank locations
			//srand(time(NULL));
			for (int i = 0; i < N; i++) {
				//math to find out where the random points will go
				int increase = increment * (i + 1);
				int Px;
				int Pz;
				//if Cx is to the left of Tx
				if (Cx < Tx) {
					if ((Cx + increase) < (abs(Cx) + abs(Tx))) {

						Px = (Cx + increase + rand() % increment + 1);
					}
				}//if Cx is the the right of Tx
				else {
					if ((Cx - increase) < (abs(Cx) + abs(Tx))) {

						Px = (Cx - increase - rand() % increment + 1);
					}
				}
				//if Cz is to the left of Tz
				if (Cz < Tz) {
					if ((Cz + increase) < (abs(Cz) + abs(Tz))) {

						Pz = (Cz + increase + rand() % increment + 1);
					}
				}//if Cz is to the right of Tz
				else {
					if ((Cz - increase) < (abs(Cz) + abs(Tz))) {

						Pz = (Cz - increase - rand() % increment + 1);
					}
				}
				//making GsMat and adding to V
				GsVec nextPoint = GsVec(Px, 0, Pz);
				V.push() = (nextPoint);
			}

			//add the last point of the tank so it will always head to tank
			V.push()=(TankLocation);

			//create al the points for the models to follow
			int t = 10000;
			for (float i = 0; i <= t; i++) {

				GsVec P = eval_bezier((float)(i / t), V);
				locations.push_back(P);
			}

		}

		~zombie() {}


};

#endif