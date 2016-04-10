#pragma once

#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "element.h"

class menu;
class gui : public element {
public:
	gui();
	gui(float width,float height);
	void loadTextures();

	void setMenu(bool m) { paused = m; }
	bool getMenu() {return paused; }
	void showGui(float wLoc, float hLoc, float menuW, float menuH);
protected:
	bool paused;
	menu *mainMenu;
};