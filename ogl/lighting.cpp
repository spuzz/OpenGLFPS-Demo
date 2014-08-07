#include "lighting.h"
#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>

using namespace std;
lighting::lighting() {

}

void lighting::setupLighting() {
	//Lighting
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f }; 				// Ambient Light Values
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };					// Diffuse Light Values
	GLfloat redDiffuseMaterial[] = {1.0, 1.0, 1.0};
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
	glEnable(GL_LIGHTING);		// Enable Lighting
	//glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT4, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT5, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glEnable(GL_LIGHT1);							// Enable Light One
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.02);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.4);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.05);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,true);
}

void lighting::positionLights() {

	GLfloat LightPosition[]= { 0.0,1.4,2.0, 1.0f };				// Light Position
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			// Position The Light

	GLfloat LightPosition4[]= { 0.0,1.4,-2.0, 1.0f };			// Light Position
	glLightfv(GL_LIGHT4, GL_POSITION,LightPosition4);			// Position The Light

	GLfloat LightPosition2[]= { -9.5,1.0,-2.0, 1.0f };			// Light Position
	glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);			// Position The Light	

	GLfloat LightPosition3[]= { 12,0.5,-0.5, 1.0f };			// Light Position
	glLightfv(GL_LIGHT3, GL_POSITION,LightPosition3);			// Position The Light	

	GLfloat LightPosition5[]= { 0,6,-12, 1.0f };				// Light Position
	glLightfv(GL_LIGHT5, GL_POSITION,LightPosition5);			// Position The Light	
}