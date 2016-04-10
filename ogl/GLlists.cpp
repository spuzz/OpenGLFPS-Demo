#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "GLlists.h"
#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "vertex.h"
using namespace std;

typedef struct
{
	float X, Y, Z;
	float U, V;
} VERTICES;
const double PI = 3.1415926535897;
const double space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES *VERTEX;

GLlists::GLlists() {
	//Output ot();
}

void GLlists::CreateSphere (double R, double H, double K, double Z) {
	int n = 0;
	double a;
	double b;
	
	VERTEX = new VERTICES[VertexCount];
	for( int b = 0;b <= 90 - space;b+=space) {
		for( int a=0;a <= 360-space;a+=space) {
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a) / 360;
			n++;

			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b  + space) / 360;
			VERTEX[n].U = (a) / 360;
			n++;

			VERTEX[n].X = R * sin((a  + space) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a  + space) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;

			VERTEX[n].X = R * sin((a  + space) / 180 * PI) * sin((b  + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a  + space) / 180 * PI) * sin((b  + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b  + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b + space) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;

		}
	}
	
}

GLuint GLlists::buildCylinder(vertex pos,float x,float y,float z,float u,float v,GLUquadricObj* quadratic,float xangle,float yangle,float zangle) {
	cylinder = glGenLists(1);
	glNewList(cylinder,GL_COMPILE);
		glTranslatef(pos.getX(),pos.getY(),pos.getZ());
		glRotatef(yangle,1.0f,0.0f,0.0f);
		glRotatef(xangle,0.0f,1.0f,0.0f);
		glRotatef(zangle,0.0f,0.0f,1.0f);
		gluCylinder(quadratic,x,y,z,u,v);	// Draw Our Cylinder
	glEndList();
	return cylinder;
}

GLuint GLlists::buildPlayer() {
	player = glGenLists(1);
	//CreateSphere(70,0,0,0);
	
	int lats = 10;
	int longs = 10;
	double radius = 0.2;
	double height = 0.25;
	glNewList(player,GL_COMPILE);
		glBegin (GL_TRIANGLE_STRIP);
		   int i, j;
		   for(i = 0; i <= lats; i++) {
			   double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
			   double z0  = sin(lat0)*radius;
			   double zr0 =  cos(lat0);
    
			   double lat1 = PI * (-0.5 + (double) i / lats);
			   double z1 = sin(lat1)*radius;
			   double zr1 = cos(lat1);
    
			   glBegin(GL_QUAD_STRIP);
			   for(j = 0; j <= longs; j++) {
				   double lng = 2 * PI * (double) (j - 1) / longs;
				   double x = cos(lng)*radius;
				   double y = sin(lng)*radius;
    
				   glNormal3f(x * zr0, y * zr0 + height, z0);
				   glVertex3f(x * zr0, y * zr0 + height, z0);
				   glNormal3f(x * zr1, y * zr1 + height, z1);
				   glVertex3f(x * zr1, y * zr1 + height, z1);
			}
           glEnd();
       }
	glEndList();
	return player;
}

GLuint GLlists::buildBullet() {
	player = glGenLists(1);
	//CreateSphere(70,0,0,0);
	int lats = 10;
	int longs = 10;
	double radius = 0.025;
	double height = 0.05;
	glColor3f(1.0,1.0,1.0);
	glNewList(player,GL_COMPILE);
		glBegin (GL_TRIANGLE_STRIP);
		   int i, j;
		   for(i = 0; i <= lats; i++) {
			   double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
			   double z0  = sin(lat0)*radius;
			   double zr0 =  cos(lat0);
    
			   double lat1 = PI * (-0.5 + (double) i / lats);
			   double z1 = sin(lat1)*radius;
			   double zr1 = cos(lat1);
    
			   glBegin(GL_QUAD_STRIP);
			   for(j = 0; j <= longs; j++) {
				   double lng = 2 * PI * (double) (j - 1) / longs;
				   double x = cos(lng)*radius;
				   double y = sin(lng)*radius;
    
				   glNormal3f(x * zr0, y * zr0 + height, z0);
				   glVertex3f(x * zr0, y * zr0 + height, z0);
				   glNormal3f(x * zr1, y * zr1 + height, z1);
				   glVertex3f(x * zr1, y * zr1 + height, z1);
			}
           glEnd();
       }
	glEndList();
	return player;
}
void GLlists::GLCall() {
	glCallList(player);
}