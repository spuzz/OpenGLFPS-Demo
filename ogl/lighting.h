#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>

#pragma once;
using namespace std;
class lighting {
 public:
	lighting();
	void setupLighting();
	void positionLights();

private:
	GLfloat* LightAmbient;
	GLfloat* LightDiffuse;
	void enableLight(int light,string type,float distance);

};