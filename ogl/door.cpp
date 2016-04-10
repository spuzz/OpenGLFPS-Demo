#include "door.h"


door::door() {
	state = 2;
	rotateX = 0;
	doorAngle = 1;
	interactive::interactive();
}

door::door(string location) {
	state = 2;
	rotateX = 0;
	doorAngle = 1;
	name = location;
	interactive::interactive(location);
}

void door::moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a) {
		glLoadIdentity();	
		glRotatef(lookupdown,1.0f,0,0);
		glRotatef(sceneroty,0,1.0f,0);
		glTranslatef(xtrans, ytrans, ztrans);
		glTranslatef(display.getPolys()[a]->getVertex(0).getX(), display.getPolys()[a]->getVertex(0).getY(), display.getPolys()[a]->getVertex(0).getZ());
		glRotatef(0 - rotateX,0,1,0);
		glTranslatef(-display.getPolys()[a]->getVertex(0).getX(), -display.getPolys()[a]->getVertex(0).getY(), -display.getPolys()[a]->getVertex(0).getZ());

}

void door::updateModel() {
	switch(state)
	{
	case 1:
		if(rotateX < 88) {
			rotateX += doorAngle;
		}
		break;
	case 2:
		if(rotateX > doorAngle) {
			rotateX -= doorAngle;
		}
		break;
		
	}
}

int door::updateState() {
	if(state == 1) {
		setColl(false);
		state = 2;
	}
	else if(state == 2) {
		setColl(true);
		state = 1;
	}
	return state;
}

