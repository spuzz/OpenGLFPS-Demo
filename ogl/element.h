#pragma once

class element {
protected:
	float width;
	float height;
	GLuint	texture[4];
	element* parent;
	GLuint	elements;

public:
	void orthogonalStart(float,float);
	void orthogonalEnd();
	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
	float getWidth() {return width; }
	float getHeight() {return height; }
	void setShape(float w, float h) { height = h; width = w; }
	virtual void loadTextures();
	virtual void createElements(float wLoc, float hLoc, float menuW, float menuH);
	virtual void showGui(float wLoc, float hLoc, float menuW, float menuH);
	void createNewList(int size);
	void addElement(float wLoc, float hLoc, float menuW, float menuH, string type);
	void setParent(element* p) { parent = p; }
	element* getParent() { return parent; }
};