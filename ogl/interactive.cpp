#include "interactive.h"

interactive::interactive() {
	overallState = 0;
	model::model();
}

void interactive::moveTo(float xtrans,float ytrans,float ztrans) {
	xPos = xtrans;
	yPos = ytrans;
	zPos = ztrans;
	xLoc = xtrans;
	yLoc = ytrans;
	zLoc = ztrans;
}

interactive::interactive(string location) {
	overallState = 0;
	model::model(location);
}

int interactive::getOverallState() {
	//cout<<"RETRIEVING INTERACTIVE"<<endl;
	return overallState;
}

void interactive::setOverallState(int a) {
	//cout<<"SETTING INTERACTIVE"<<endl;
	overallState = a;
}
