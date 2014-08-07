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
#include "button.h"
using namespace std;


class menu : public element {
private:
	void createButtons();
public:
	menu();
	menu(float,float);
	void loadTextures();
	virtual void showGui(float wLoc, float hLoc, float menuW, float menuH);
	vector<button*> buttons;
	virtual void createElements(float wLoc, float hLoc, float menuW, float menuH);
};