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


class bullet : public interactive{
private:
	void moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a);
	void modelHit();
	float aliveTime;
	int maxAliveTime;
	float dirCoef;
	float rotateX, doorAngle;
	void updateModel();
public:
	bullet(float xtrans,float ytrans,float ztrans,float xDir,float yDir,float zDir);
	bullet(string location,float xtrans,float ytrans,float ztrans,float xDir,float yDir,float zDir);
	void incrementAlive();
	void setAlive(int alive) {aliveTime= alive;}
	void setOverallState(int);
	int getOverallState();
	int getAlive() {return aliveTime;}
	int updateState();
};