#pragma once

class vertex {
public:
	vertex();
	vertex(float inX,float inY, float inZ, float inU, float inV);
	void setX(float inX) {x = inX; }
	void setY(float inY) {y = inY; }
	void setZ(float inZ) {z = inZ; }
	void setU(float inU) {u = inU; }
	void setV(float inV) {v = inV; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getU() { return u; }
	float getV() { return v; }

private:
	float x,y,z;
	float u,v;
};