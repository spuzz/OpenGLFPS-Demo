#include <vector>

#pragma once;
using namespace std;
class ColVector {
 public:
	ColVector();
	ColVector(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float);
	void setY(float);
	void setZ(float);
	vector<float> getVector();
	static float dotProduct(const vector<float>, const vector<float>);
	static vector<float> crossProduct(const vector<float>, const vector<float>);
	static vector<float> subtract(const vector<float>, const vector<float>);
	static vector<float> add(const vector<float>, const vector<float>);
	static vector<float> divide(const vector<float>, const vector<float>);
	static vector<float> divide(const vector<float>, const float);
	static vector<float> multiply(const vector<float>, const vector<float>);
	static float magnitude(const vector<float>);
	static vector<float> unit(const vector<float> vN1,float magnitude);
private:
	vector<float> vec;
};