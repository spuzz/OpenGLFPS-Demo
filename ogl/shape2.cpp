#include <vector>
#include "shape2.h"

using namespace std;

shape2::shape2() {
	currentPoly = -1;
	//Output ot;
}
void shape2::newPoly() {
	currentPoly += 1;
	polygon poly;
	polys.push_back(poly);
}

void shape2::addVertex(float inX,float inY,float inZ,float inU,float inV) {
	//ot.out(currentPoly);
	polys[currentPoly].addVertex(inX,inY,inZ,inU,inV);
}
