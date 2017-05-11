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
# include "time.h"

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

	int changed = -1;
	int currentStep = 0;

	int RATD = 1;
	int LATD = 1;
	int RLTD = 1;
	int LLTD = 1;

	float RAT = -(GS_PI / 2);
	float LAT = -(GS_PI / 2);
	float RLT = 0;
	float LLT = 0;

	GsMat currentLocation;
	GsMat TankCurrentLocation;
	std::vector<GsVec> locations;

	float T = 0.0f;
	GsMat RotateToNext =
		GsMat( //rotations of the right arm
			cos(T), 0.0f, -sin(T), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin(T), 0.0f, cos(T), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

	GsMat RArmOuts =
		GsMat( //rotations of the right arm
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(RAT), -sin(RAT), 0.0f,
			0.0f, sin(RAT), cos(RAT), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

	GsMat LArmOuts =
		GsMat( //rotations of the right arm
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(LAT), -sin(LAT), 0.0f,
			0.0f, sin(LAT), cos(LAT), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	GsMat ArmUp =
		GsMat( //rotations of the right arm
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.125f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	GsMat MoveAboveOrigin =
		GsMat( //rotations of the right arm
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.15f,
			0.0f, 0.0f, 1.0f, 0.0f,
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
					1.0f, 0.0f, 0.0f, (float)(rand() % 5 + 5),
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, (float)(rand() % 5 + 5),
					0.0f, 0.0f, 0.0f, 1.0f
					);
		}
		else {
			currentLocation =
				GsMat(
					1.0f, 0.0f, 0.0f, (float)-(rand() % 5 + 5),
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, (float)-(rand() % 5 + 5),
					0.0f, 0.0f, 0.0f, 1.0f
					);
		}

		/*
		if (ran == 0) {
		currentLocation =
		GsMat(
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
		}
		else {
		currentLocation =
		GsMat(
		1.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
		}
		*/

		body.build(2 * scale, 1 * scale, 3 * scale);
		head.build(2 * scale, 2 * scale, 2 * scale);
		LeftArm.build(1 * scale, 1 * scale, 3 * scale);
		RightArm.build(1 * scale, 1 * scale, 3 * scale);
		LeftLeg.build(1 * scale, 1 * scale, 3 * scale);
		RightLeg.build(1 * scale, 1 * scale, 3 * scale);

		changed = 1;
	}

	void drawZombie(const GsMat& stransf, const GsMat& sproj, const GsLight& _light) {

		RotateToNext =
			GsMat( //rotations of the body
				cos(T), 0.0f, -sin(T), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				sin(T), 0.0f, cos(T), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);
		RArmOuts =
			GsMat( //rotations of the right arm
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(RAT), -sin(RAT), 0.0f,
				0.0f, sin(RAT), cos(RAT), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);
		LArmOuts =
			GsMat( //rotations of the left arm
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(LAT), -sin(LAT), 0.0f,
				0.0f, sin(LAT), cos(LAT), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);

		GsMat RLegOuts =
			GsMat( //rotations of the right leg
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(RLT), -sin(RLT), 0.0f,
				0.0f, sin(RLT), cos(RLT), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);
		GsMat LLegOuts =
			GsMat( //rotations of the left leg
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(LLT), -sin(LLT), 0.0f,
				0.0f, sin(LLT), cos(LLT), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);

		body.draw(stransf*currentLocation*MoveAboveOrigin*RotateToNext, sproj, _light);
		head.draw(stransf*currentLocation*MoveAboveOrigin*RotateToNext, sproj, _light);
		LeftArm.draw(stransf*currentLocation*ArmUp*MoveAboveOrigin*RotateToNext*LArmOuts, sproj, _light);
		RightArm.draw(stransf*currentLocation*ArmUp*MoveAboveOrigin*RotateToNext*RArmOuts, sproj, _light);
		LeftLeg.draw(stransf*currentLocation*MoveAboveOrigin*RotateToNext*RLegOuts, sproj, _light);
		RightLeg.draw(stransf*currentLocation*MoveAboveOrigin*RotateToNext*LLegOuts, sproj, _light);
	}

	void updateArms() {
		if (RATD == 1) {
			if (RAT > -(3 * GS_PI / 4))
				RAT -= 0.01;
			else
				RATD = 0;
		}
		else {
			if (RAT < -(GS_PI / 4))
				RAT += 0.01;
			else
				RATD = 1;
		}
		///////// moves oppisite of Right Arm
		if (LATD == 0) {
			if (LAT > -(3 * GS_PI / 4))
				LAT -= 0.01;
			else
				LATD = 1;
		}
		else {
			if (LAT < -(GS_PI / 4))
				LAT += 0.01;
			else
				LATD = 0;
		}
	}

	void updateLegs() {
		if (RLTD == 1) {
			if (RLT > -(GS_PI / 5))
				RLT -= 0.01;
			else
				RLTD = 0;
		}
		else {
			if (RLT < (GS_PI / 5))
				RLT += 0.01;
			else
				RLTD = 1;
		}
		///////// moves oppisite of Right Leg
		if (LLTD == 0) {
			if (LLT > -(GS_PI / 5))
				LLT -= 0.01;
			else
				LLTD = 1;
		}
		else {
			if (LLT < (GS_PI / 5))
				LLT += 0.01;
			else
				LLTD = 0;
		}
	}

	//deletes the last 300 points and adds a new 300 to the vector
	void updateVectorLocations(GsMat TankLocation) {

		if (currentStep < 9000) {

			//				for (int i = 0; i < 1000; i++) {
			//					locations.pop_back();
			//				}
			locations.erase(locations.begin() + 9000, locations.end());

			GsArray<GsVec> V;
			V.push() = GsVec(currentLocation[3], 0, currentLocation[11]);
			//add the last point of the tank so it will always head to tank
			V.push() = GsVec(TankLocation[3], 0, TankLocation[11]);

			int t = 1000;
			for (float i = 0; i < t; i++) {
				GsVec P = eval_bezier((float)(i / t), V);
				locations.push_back(P);
			}
		}
	}

	//you pass a int that is the step in the curve
	void updateLocation(int i) {

		currentLocation[3] = locations[i].x;
		currentLocation[11] = locations[i].z;

		float x = locations[i + 1].x - locations[i].x;
		float z = locations[i + 1].z - locations[i].z;

		T = -atan2(x, z);
		//			printf("%f \n", T);
		if (currentStep < 9990) {
			currentStep += 1;
		}
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

	GsVec eval_lagrange(float t, const GsArray<GsVec>& points) {

		GsVec location;
		location.x = 0.0f;
		location.y = 0.0f;
		location.z = 0.0f;

		float b;
		int N = points.size();

		GsArray<float> a;

		for (int i = 0; i < points.size(); i++) {

			a.push((i*1.0f) / (float)(points.size() - 1));
		}

		for (int i = 0; i < N; i++) {

			b = 1.0;
			for (int j = 0; j < N; j++) {

				if (j == i) {
					continue;
				}

				b = b * ((t - a[j]) / (a[i] - a[j]));
			}
			location = location + points[i] * b;
		}

		return location;
	}

	void pathing(GsMat TankLocation) {

		//delets all elements in locations
		locations.clear();

		GsArray<GsVec> V;

		V.push() = GsVec(currentLocation[3], 0, currentLocation[11]);
		//			V.push() = GsVec(currentLocation[3], 0, currentLocation[11]);

		//stores locations and fins distance
		int N = 4;
		int Cx = currentLocation[3];// = currentLocation.x;
		int Cz = currentLocation[11];// = currentLocation.z;
		int Tx = TankLocation[3];
		int Tz = TankLocation[11];

		int distance = sqrt((Tx - Cx)*(Tx - Cx) + (Tz - Cz)*(Tz - Cz));
		int increment = distance / (N + 1);
		//adds in N random control points between current and tank locations
		srand(time(NULL));
		for (int i = 0; i < N; i++) {
			//math to find out where the random points will go
			int increase = increment * (i + 1);
			int Px = 0;
			int Pz = 0;
			//if Cx is to the left of Tx
			if (Cx < Tx) {
				if ((Cx + increase) < (abs(Cx) + abs(Tx))) {

					Px = (Cx + increase + rand() % 5 + 1);
				}
			}//if Cx is the the right of Tx
			else {
				if ((Cx - increase) < (abs(Cx) + abs(Tx))) {

					Px = (Cx - increase - rand() % 5 + 1);
				}
			}
			//if Cz is to the left of Tz
			if (Cz < Tz) {
				if ((Cz + increase) < (abs(Cz) + abs(Tz))) {

					Pz = (Cz + increase + rand() % 5 + 1);
				}
			}//if Cz is to the right of Tz
			else {
				if ((Cz - increase) < (abs(Cz) + abs(Tz))) {

					Pz = (Cz - increase - rand() % 5 + 1);
				}
			}
			//making GsMat and adding to V
			GsVec nextPoint = GsVec(Px, 0, Pz);
			V.push() = (nextPoint);
		}

		//add the last point of the tank so it will always head to tank
		V.push() = GsVec(TankLocation[3], 0, TankLocation[11]);
		//			V.push() = GsVec(TankLocation[3], 0, TankLocation[11]);
		/*
		for (int i = 0; i < V.size(); i++) {

		printf("Point %d (%f,%f,%f)\n", i, V[i].x, V[i].y, V[i].z);
		}
		*/
		//create al the points for the models to follow
		int t = 10000;
		for (float i = 0; i < t; i++) {

			//				GsVec P = eval_bezier((float)(i / t), V);
			GsVec P = eval_lagrange((float)(i / t), V);

			locations.push_back(P);
		}
		/*
		for (int j = 0; j < V.size() - 3; j++) {

		GsArray<GsVec> pnts;
		pnts.push() = V[j]; pnts.push() = V[j + 1];
		pnts.push() = V[j + 2]; pnts.push() = V[j + 3];
		for (float i = 0; i <= t; i++) {

		GsVec P = eval_crspline((float)(i / t), pnts);
		locations.push_back(P);
		}
		}
		*/
		changed = -1;
	}

	~zombie() {}


};

#endif