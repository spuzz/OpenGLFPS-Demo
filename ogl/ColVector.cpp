#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <iostream>
#include <vector>
#include "ColVector.h"
using namespace std;

ColVector::ColVector() {

}
ColVector::ColVector(float x, float y, float z) {

	vec.push_back(x);
	vec.push_back(y);
	vec.push_back(z);
}

float ColVector::dotProduct(vector<float> vec1, vector<float> vec2) {
	float tmp;
	for(int a=0;a<vec1.size();a++) {
		tmp += vec1[a]*vec2[a];
	}
	return tmp;
}

float ColVector::magnitude(const vector<float> vN1) {
	return sqrtf((vN1[0]*vN1[0]) + (vN1[1]*vN1[1]) + (vN1[2]*vN1[2]));
}

vector<float> ColVector::unit(const vector<float> vN1,float magnitude) {
	vector<float> tmp;
	tmp.push_back(vN1[0]/magnitude);
	tmp.push_back(vN1[1]/magnitude);
	tmp.push_back(vN1[2]/magnitude);
	return tmp;
}
vector<float> ColVector::crossProduct(const vector<float> vN1, const vector<float> vN2) {
	vector<float> tmp;
	tmp.push_back((vN1[1] * vN2[2]) - (vN1[2] * vN2[1]));
	tmp.push_back((vN1[2] * vN2[0]) - (vN1[0] * vN2[2]));
	tmp.push_back((vN1[0] * vN2[1]) - (vN1[1] * vN2[0]));
	return tmp;
}

vector<float> ColVector::subtract(const vector<float> vN1, const vector<float> vN2) {
	vector<float> tmp;
	tmp.push_back(vN1[0] - vN2[0]);
	tmp.push_back(vN1[1] - vN2[1]);
	tmp.push_back(vN1[2] - vN2[2]);
	return tmp;
}

vector<float> ColVector::add(const vector<float> vN1, const vector<float> vN2) {
	vector<float> tmp;
	tmp.push_back(vN1[0] + vN2[0]);
	tmp.push_back(vN1[1] + vN2[1]);
	tmp.push_back(vN1[2] + vN2[2]);
	return tmp;
}


vector<float> ColVector::divide(const vector<float> vN1, const vector<float> vN2) {
		vector<float> tmp;
	tmp.push_back(vN1[0] + vN2[0]);
	tmp.push_back(vN1[1] + vN2[1]);
	tmp.push_back(vN1[2] + vN2[2]);
	return tmp;
}

vector<float> ColVector::divide(const vector<float> vN1, float div) {
		vector<float> tmp;
	tmp.push_back(vN1[0]/div);
	tmp.push_back(vN1[1]/div);
	tmp.push_back(vN1[2]/div);
	return tmp;
}

float ColVector::getX() {
		return vec[0];
}

float ColVector::getY() {
		return vec[1];
}

float ColVector::getZ() {
		return vec[2];
}


void ColVector::setX(float x) {
	vec[0] = x;
}

void ColVector::setY(float y) {
	vec[1] = y;
}

void ColVector::setZ(float z) {
	vec[2] = z;
}

vector<float> ColVector::getVector() {
	return vec;
}