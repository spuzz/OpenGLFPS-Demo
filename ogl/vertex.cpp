#include <vector>
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include "vertex.h"

vertex::vertex() {
	x = 0;
	y = 0;
	z = 0;
	u = 0;
	v = 0;
}

vertex::vertex(float inX,float inY,float inZ,float inU,float inV) {
	x = inX;
	y = inY;
	z = inZ;
	u = inU;
	v = inV;
}