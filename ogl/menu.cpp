#include "menu.h"
#include "texLoad.h"
#include "button.h"

menu::menu() {
	loadTextures();
}

menu::menu(float width,float height) {
	loadTextures();
	//gu = guiP;
	//element:gui(width,height);
}

void menu::createButtons() {

}
void menu::createElements(float wLoc, float hLoc, float menuW, float menuH) {
	elements = glGenLists(2);								// Building Two Lists
	glNewList(elements,GL_COMPILE);							// New Compiled box Display List
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
void menu::loadTextures() {
	texture[0] = texLoad::LoadGLTextures("Data/carpet.bmp",texture[0]);
	float menuH = (height/2 + height/4) - (height/2 - height/4);
	float menuW = (width/2 + width/4) - (width/2 - width/4);
	createElements(width/2 - width/4,height/2 - height/4,menuW,menuH);
}

void menu::showGui(float wLoc, float hLoc, float menuW, float menuH) {
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	orthogonalStart(width,height);
	glEnable(GL_POLYGON_OFFSET_FILL); // Avoid Stitching!
	glPolygonOffset(1.0, 1.0);
	glCallList(elements);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glLineWidth(5.0);
	glColor3f(1.0,0.0,0.0); // Color for your polygon border
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(elements);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0);

	orthogonalEnd();
	createButtons();
}