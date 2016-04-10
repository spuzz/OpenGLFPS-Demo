#pragma once

#include <windows.h>
#include <vector>
#include <iostream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>
#include "Output.h"
#include "polygon.h"
using namespace std;

class shape {
public:
	shape();
	vector<polygon*> getPolys() { return polys; }
	void setPolys(vector<polygon*> newPoly) { polys = newPoly; }
	void newPoly();
	void addVertex(float inX,float inY,float inZ,float inU,float inV);


private:
	int currentPoly;
	vector<polygon*> polys;
	//Output ot;
	polygon* poly;
};