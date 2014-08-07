#pragma once

#include <vector>
#include "vertex.h"
#include "Output.h"
using namespace std;

class polygon {
public:
	polygon();
	int getShape() { return totalVert; }
	void addVertex(float x, float y, float z, float u, float v);
	void changeVertex(int vectorLoc, float x, float y, float z, float u, float v);
	vertex getVertex(int vectorLoc);
	int getTotalVert() { return totalVert; }
	void incTotalVert() { totalVert += 1; }
	vector<float> getNormal() { return vNorm; }
	vector<float> vNorm;
private:
	vector<vertex> vertices;
	int totalVert;

};