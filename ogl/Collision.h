#include <vector>
#include <stdio.h>			// Header File For Standard Input/Output
#include <iostream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include "Output.h"
#include "model.h"
#pragma once

using namespace std;

class Collision {
public:
	bool collisionTest(vector<float> startPoint,vector<float> direction);
	Collision();
	Collision(vector<model*> sector,bool select);
	void setSector(vector<model*> sector);
	float calculateHeight();
	bool checkColl();
	vector<model*> getSector();
	bool Collision::cylinderColl(model* mod,vector<float> start, vector<float> direction);
protected:
	vector<float> vNorm;
	bool sel;
	bool updated;
	int ClassifyPoint(vector<float> vNorm, vector<float> pt, float distance, bool prt);
	vector<model*> sector1;
	vector<float> intersect;
};
