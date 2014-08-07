#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <string>
#include "model.h"
#include <vector>
#include "fakemodel.h"

#pragma once
using namespace std;


class ModelControl {
public:
	ModelControl();
	void build(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans);
	void spawnSprite(string type,float xtrans,float ytrans,float ztrans);
	void spawnBullet(float xtrans,float ytrans,float ztrans,float xDir,float yDir,float zDir);
	void checkCollision(vector<model*>);
	vector<model*> getModels() { return models; }

private:
	vector<model*> models;
	vector<model> testing;
	fakemodel* newModel;
	Output ot;
};