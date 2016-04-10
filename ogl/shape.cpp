#include <vector>
#include "shape.h"

using namespace std;

shape::shape() {
	currentPoly = -1;
	//Output ot;
}
void shape::newPoly() {
	currentPoly += 1;
	poly = new polygon();
	polys.push_back(poly);
}

void shape::addVertex(float inX,float inY,float inZ,float inU,float inV) {
	polys[currentPoly]->addVertex(inX,inY,inZ,inU,inV);
}
