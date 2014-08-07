#pragma once

#include <windows.h>
#include <vector>
#include <iostream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include "shape.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>
#include "Output.h"
#include "model.h"

using namespace std;


class interactive : public model{
protected:
	//int overallState;

public:
	interactive();
	interactive(string location);
	void moveTo(float xtrans,float ytrans,float ztrans);
	virtual int getOverallState();
	virtual void setOverallState(int);
};