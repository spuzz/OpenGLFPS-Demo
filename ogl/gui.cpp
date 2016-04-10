#include "gui.h"
#include "menu.h"
#include "element.h"
#include "texLoad.h"

gui::gui() {

}

gui::gui(float w,float h) {
	width = w;
	height = h;
}

void gui::loadTextures() {
	texture[0] = texLoad::LoadGLTextures("Data/carpet.bmp",texture[0]);
	float menuH = (height/2 + height/4) - (height/2 - height/4);
	float menuW = (width/2 + width/4) - (width/2 - width/4);
	mainMenu = new menu(width,height);
	//newmenu.createElements(width/2 - width/4,height/2 - height/4,menuW,menuH);
	mainMenu->loadTextures();
}

void gui::showGui(float wLoc, float hLoc, float menuW, float menuH) {
	
	glLoadIdentity();	

	
	if(paused == true) {
		float menuH = (height/2 + height/4) - (height/2 - height/4);
		float menuW = (width/2 + width/4) - (width/2 - width/4);
		
		mainMenu->setShape(width,height);
		mainMenu->setParent(this);
		mainMenu->showGui(width/2 - width/4,height/2 - height/4,menuW,menuH);
	}
	orthogonalStart(width,height);

	glColor3f(1.0,1.0,1.0); // Color for your polygon border
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_POLYGON_OFFSET_FILL); // Avoid Stitching!
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, 0);
	glTexCoord2f(1.0,0.0);
	glVertex2f(0, height/12);
	glTexCoord2f(1.0,1.0);
	glVertex2f(width, height/12);
	glTexCoord2f(0.0,1.0);	
	glVertex2f(width, 0);
	
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);

	glLineWidth(5.0);
	glColor3f(1.0,0.0,0.0); // Color for your polygon border
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, 0);
	glTexCoord2f(1.0,0.0);
	glVertex2f(0, height/12);
	glTexCoord2f(1.0,1.0);
	glVertex2f(width, height/12);
	glTexCoord2f(0.0,1.0);	
	glVertex2f(width, 0);
	
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0);


	glColor3f(1.0,1.0,1.0); // Color for your polygon border
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_POLYGON_OFFSET_FILL); // Avoid Stitching!
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, height - height/5);
	glTexCoord2f(1.0,0.0);
	glVertex2f(0, height);
	glTexCoord2f(1.0,1.0);
	glVertex2f(width, height);
	glTexCoord2f(0.0,1.0);	
	glVertex2f(width, height - height/5);
	
	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);

	glLineWidth(5.0);
	glColor3f(1.0,0.0,0.0); // Color for your polygon border
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, height - height/5);
	glTexCoord2f(1.0,0.0);
	glVertex2f(0, height);
	glTexCoord2f(1.0,1.0);
	glVertex2f(width, height);
	glTexCoord2f(0.0,1.0);	
	glVertex2f(width, height - height/5);
	
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0);
	orthogonalEnd();
}
