#include "model.h"

model::model() {
}

model::model(string type) {
	name = type;

}

void model::build(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {

	if(displayType != true) {
		buildModel(lookupdown,sceneroty,xtrans, ytrans, ztrans);
	}
	else {
		buildList(lookupdown,sceneroty,xtrans, ytrans, ztrans);
	}
}

void model::moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a) {

}


void model::modelHit() {

}

void model::updateModel() {

}

int model::updateState() {
	return 2;
}

int model::getOverallState() {
	return 0;
}

void model::setOverallState(int a) {
}

void model::calculateMath() {
	if(!display.getPolys().size() == 0) {
		for(int a = 0; a<display.getPolys().size() - 1;a++) {
			display.getPolys()[a]->vNorm = calculateNormal(display.getPolys()[a]);
		}
	}
}

void model::buildModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
	GLfloat x_m, y_m, z_m, u_m, v_m;

	for(int a = 0; a<display.getPolys().size() - 1;a++) {
		moveModel(lookupdown,sceneroty,xtrans, ytrans, ztrans,a);
		glBegin(GL_POLYGON);
		//if(display.getPolys()[a]->getTotalVert() == 3) {
		//	
		//	glBegin(GL_TRIANGLES);

		//}
		//else if(display.getPolys()[a]->getTotalVert() == 4) {
		//	glBegin(GL_QUADS);
		//}
		//else {
		//	glBegin(GL_POLYGON);
		//}
		glNormal3f( display.getPolys()[a]->vNorm[0], display.getPolys()[a]->vNorm[1], display.getPolys()[a]->vNorm[2]);
		for(int b = 0; b<display.getPolys()[a]->getTotalVert();b++) {

			x_m = display.getPolys()[a]->getVertex(b).getX();
			y_m = display.getPolys()[a]->getVertex(b).getY();
			z_m = display.getPolys()[a]->getVertex(b).getZ();
			u_m = display.getPolys()[a]->getVertex(b).getU();
			v_m = display.getPolys()[a]->getVertex(b).getV();
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
		
		}
		glEnd();
	}
	updateModel();
}

void model::buildList(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
	moveModel(lookupdown,sceneroty,xtrans,ytrans,ztrans,0);
	glCallList(displayList);
}

vector<float> model::calculateNormal(polygon* poly) {
	vector<float> vN1;
	vector<float> vN2;
	vector<float> vNorm;
	//vector<float> p1;
	//vector<float> p2;
	//vector<float> p3;
	//p1.push_back(poly->getVertex(1).getX());
	//p1.push_back(poly->getVertex(1).getY());
	//p1.push_back(poly->getVertex(1).getZ());
	//p2.push_back(poly->getVertex(0).getX());
	//p2.push_back(poly->getVertex(0).getY());
	//p2.push_back(poly->getVertex(0).getZ());
	//p3.push_back(poly->getVertex(2).getX());
	//p3.push_back(poly->getVertex(2).getY());
	//p3.push_back(poly->getVertex(2).getZ());

	vN1.push_back(poly->getVertex(1).getX() - poly->getVertex(0).getX());
	vN1.push_back(poly->getVertex(1).getY() - poly->getVertex(0).getY());
	vN1.push_back(poly->getVertex(1).getZ() - poly->getVertex(0).getZ());

	vN2.push_back(poly->getVertex(2).getX() - poly->getVertex(1).getX());
	vN2.push_back(poly->getVertex(2).getY() - poly->getVertex(1).getY());
	vN2.push_back(poly->getVertex(2).getZ() - poly->getVertex(1).getZ());

	vNorm.push_back(vN1[1] * vN2[2] - vN1[2] * vN2[1]);
	vNorm.push_back(vN1[2] * vN2[0] - vN1[0] * vN2[2]);
	vNorm.push_back(vN1[0] * vN2[1] - vN1[1] * vN2[0]);

	float magnitude = sqrt((vNorm[0]*vNorm[0]) + (vNorm[1]*vNorm[1]) + (vNorm[2]*vNorm[2]));
	vNorm[0] = vNorm[0]/magnitude;
	vNorm[1] = vNorm[1]/magnitude;
	vNorm[2] = vNorm[2]/magnitude;

	return vNorm;
}
//shape model::getShape() {
//	return display;
//}