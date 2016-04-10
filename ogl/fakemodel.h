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
#include "GLlists.h"

using namespace std;

class fakemodel {
public:
	fakemodel();
	fakemodel(string name);

	//shape display;
	//void calculateMath();
	//void buildDisplayList();
	//void build(float,float,float,float,float);
	//virtual void moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a);
	//virtual void updateModel();
	//virtual int updateState();
	//virtual int getOverallState();
	//virtual void modelHit();

	//shape getShape();
	//string getName() { return name; }
	//void setDisplayType(bool type) { displayType = type; }
	//void setColl(bool col) { collision = col; }
	//vector<float> calculateNormal(polygon*);
	//float getXpos() { return xPos; };
	//float getYpos() { return yPos; };
	//float getZpos() { return zPos; };
	//float getXloc() { return xLoc; };
	//float getYloc() { return yLoc; };
	//float getZloc() { return zLoc; };
	//float getXdir() { return xDir; };
	//float getYdir() { return yDir; };
	//float getZdir() { return zDir; };
	//

	//bool getColl() { return collision; }

protected:
	//bool collision;
	//int state;
	//bool displayType;
	//float xDir,yDir,zDir,xLoc,yLoc,zLoc;
	//float xPos,yPos,zPos;
	//string name;
	//GLuint texture;
	//GLuint displayList;
	//GLlists disList;
	//void buildList(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans);
	//void buildModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans);
};