#pragma once

#include <windows.h>
#include <vector>
#include <iostream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include "shape.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>
#include "Output.h"
#include "model.h"
#include "interactive.h"

using namespace std;


class player : public interactive{
private:
	void moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a);
	float rotateX, doorAngle;
	void updateModel();
public:
	player(float xtrans,float ytrans,float ztrans);
	player(string location, float xtrans,float ytrans,float ztrans);
	int updateState();
};