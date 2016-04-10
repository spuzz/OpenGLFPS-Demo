#include "polygon.h"


polygon::polygon() {
	totalVert = 0;
}

void polygon::addVertex(float x, float y, float z, float u, float v) {
	totalVert += 1;
	vertices.push_back(vertex(x,y,z,u,v));
	
}

void polygon::changeVertex(int vectorLoc, float x, float y, float z, float u, float v) {
	vertices[vectorLoc].setX(x);
	vertices[vectorLoc].setY(y);
	vertices[vectorLoc].setZ(z);
	vertices[vectorLoc].setU(u);
	vertices[vectorLoc].setZ(v);
}

vertex polygon::getVertex(int vectorLoc) {
	return vertices[vectorLoc];
}
