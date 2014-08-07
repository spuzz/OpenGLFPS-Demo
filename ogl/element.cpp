#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
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
#include "element.h"
#include "texLoad.h"

void element::orthogonalStart(float width, float height) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glScalef(1, -1, 1);
	glTranslatef(0, -height, 0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void element::orthogonalEnd () {
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void element::addElement(float wLoc, float hLoc, float menuW, float menuH, string type) {
	glNewList(elements,GL_COMPILE);	
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);	
			glVertex2f(wLoc, hLoc); 
			glTexCoord2f(1.0,0.0);	
			glVertex2f(wLoc, hLoc + menuH);
			glTexCoord2f(1.0,1.0);	
			glVertex2f(wLoc + menuW,hLoc + menuH);
			glTexCoord2f(0.0,1.0);	
			glVertex2f(wLoc + menuW, hLoc);
		glEnd();
	glEndList();
}

void element::createNewList(int size) {

}

void element::loadTextures() {

}

void element::showGui(float wLoc, float hLoc, float menuW, float menuH) {

}

void element::createElements(float wLoc, float hLoc, float menuW, float menuH) {

}
