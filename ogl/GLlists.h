#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <string>
#include "vertex.h"

#pragma once
using namespace std;


class GLlists {
public:
	GLlists();
	GLuint buildPlayer();
	GLuint buildBullet();
	GLuint buildCylinder(vertex pos,float x,float y,float z,float u,float v,GLUquadricObj* quadratic,float xangle,float yangle,float zangle);
	void CreateSphere(double R, double H, double K, double Z);
	void GLCall();


private:
	GLuint player;										// Storage For The Display List
	GLuint cylinder;
	//Output ot;
	int type;
};