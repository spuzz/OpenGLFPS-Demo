#include "ModelControl.h"
#include "player.h"
#include "bullet.h"
#include "gui.h"
#include "Collision.h"
#include "ColVector.h"
#include "time.h";

ModelControl::ModelControl() {

}

void ModelControl::build(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
	for(int a=0; a<models.size(); a++) {
		if(models[a]->getOverallState() == 0) {
			int result = models[a]->updateState();
			models[a]->build(lookupdown,sceneroty,xtrans, ytrans, ztrans);
		}
	}
	bool removeDead = true;
	
	if(models.size() > 0) {
		while(removeDead && models.size() > 0) {
			
			if(models.front()->getOverallState() == 1) {
				models.erase(models.begin());
				
			}
			else {
				removeDead = false;
			}
		}
	}

}

void ModelControl::checkCollision(vector<model*> modelColCheck) {

	Collision collision(modelColCheck,false);
	for(int a=0; a<models.size(); a++) {
		ColVector start(models[a]->getXloc(),models[a]->getYloc(),models[a]->getZloc());
		ColVector direction((models[a]->getXdir()*0.2),(models[a]->getYdir()),models[a]->getZdir()*0.2);
		bool detect = collision.collisionTest(start.getVector(),direction.getVector());
		if(detect == true) {
			models[a]->modelHit();
			
		}
	}

}

void ModelControl::spawnSprite(string type,float xtrans,float ytrans,float ztrans) {
	if(type == "player") {
		model* newModel;
		newModel = new player(xtrans,ytrans,ztrans);
		newModel->setDisplayType(true);
		newModel->setPolyType("player");
		models.push_back(newModel);
	}
}

void ModelControl::spawnBullet(float xtrans,float ytrans,float ztrans,float xDir,float yDir,float zDir) {
		if(models.size() < 100) {
			model* newModel = new bullet(xtrans,ytrans,ztrans,xDir,yDir,zDir);
			newModel->setDisplayType(true);
			newModel->setPolyType("bullet");
			models.push_back(newModel);
		}

}