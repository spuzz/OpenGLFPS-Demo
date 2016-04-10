#include "bullet.h"


bullet::bullet(float xtrans,float ytrans,float ztrans,float xDirec,float yDirec,float zDirec) {
	state = 2;
	aliveTime = 0;
	xDir = xDirec;
	yDir = yDirec;
	zDir = zDirec;
	moveTo(xtrans,ytrans,ztrans);
	displayList = disList.buildBullet();
	maxAliveTime = 50;
	dirCoef = 1;
	model::model();
}

bullet::bullet(string location,float xtrans,float ytrans,float ztrans,float xDirec,float yDirec,float zDirec) {
	moveTo(xtrans,ytrans,ztrans);
	aliveTime = 0;
	xDir = xDirec;
	yDir = yDirec;
	zDir = zDirec;
	state = 2;
	name = location;
	maxAliveTime = 50;
	dirCoef = 1;
	model::model(location);
	
}

void bullet::moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a) {
		glLoadIdentity();	
		glRotatef(lookupdown,1.0f,0,0);
		glRotatef(sceneroty,0,1.0f,0);
		glTranslatef(xtrans + xLoc, ytrans + yLoc, ztrans + zLoc);

}

void bullet::modelHit() {
	dirCoef = dirCoef*(-1);
}

void bullet::updateModel() {
	xLoc = xLoc + xDir*0.2*dirCoef;
	yLoc = yLoc + yDir*0.2*dirCoef;
	zLoc = zLoc + zDir*0.2*dirCoef;
}

int bullet::updateState() {
	if(state == 1) {
		//setColl(true);
		state = 2;
	}
	else if(state == 2) {
		incrementAlive();
	}
	return overallState;
}


void bullet::setOverallState(int a) {
	//cout<<"SETTING BULLET"<<endl;
	overallState = a;
}

int bullet::getOverallState() {
	//cout<<"RETRIEVING BULLET"<<endl;
	return overallState;
}

void bullet::incrementAlive() {
	aliveTime += 1;
	if(aliveTime > maxAliveTime) {
		setOverallState(1);
	}
	else {
		updateModel();
	}
}

