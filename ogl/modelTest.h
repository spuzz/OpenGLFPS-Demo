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

class model {
public:
	model();
	model(string name);
	void buildDisplayList();
	void build(float,float,float,float,float);
	virtual void moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a);
	virtual void updateModel();
	virtual void updateState();
	virtual int getOverallState();
	shape getShape();
	string getName() { return name; }
	shape display;
	void setDisplayType(bool type) { displayType = type; }
	void setColl(bool col) { collision = col; }
	bool getColl() { return collision; }

protected:
	bool collision;
	int state;
	bool displayType;
	string name;
	//GLuint texture;
	//GLuint displayList;
	//Output ot;
	//GLlists disList;
	void buildList(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans);
	void buildModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans);
};