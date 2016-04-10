#pragma once
#include "gui.h"

class button : public element {
private:
	bool selected;
public:
	button();
	void loadTextures();
	void pushed();
};