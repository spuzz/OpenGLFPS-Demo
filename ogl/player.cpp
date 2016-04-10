#include "player.h"

player::player(float xtrans,float ytrans,float ztrans) {
	moveTo(xtrans,ytrans,ztrans);
	displayList = disList.buildPlayer();
	model::model();
}

player::player(string location,float xtrans,float ytrans,float ztrans) {
	moveTo(xtrans,ytrans,ztrans);
	state = 2;
	displayList = disList.buildPlayer();
	model::model(location);
}

void player::moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a) {
		glLoadIdentity();	
		glRotatef(lookupdown,1.0f,0,0);
		glRotatef(sceneroty,0,1.0f,0);
		glTranslatef(xtrans + xPos, ytrans + yPos, ztrans + zPos);
		//glTranslatef(display.getPolys()[a]->getVertex(0).getX(), display.getPolys()[a]->getVertex(0).getY(), display.getPolys()[a]->getVertex(0).getZ());
		//glRotatef(0 - rotateX,0,1,0);
		//glTranslatef(-display.getPolys()[a]->getVertex(0).getX(), -display.getPolys()[a]->getVertex(0).getY(), -display.getPolys()[a]->getVertex(0).getZ());

}

void player::updateModel() {

}

int player::updateState() {
	return 2;
}

