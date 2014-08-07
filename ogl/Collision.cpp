
#include "Output.h"
#include "ColVector.h"
#include "Collision.h"
#include <vector>
#include <stdio.h>			// Header File For FStandard Input/Output
#include <iostream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
using namespace std;

const double PI = 3.141592;

Collision::Collision() {
}

Collision::Collision(vector<model*> sector,bool select) {
	updated = true;
	sel = select;
	sector1 = sector;
}

void Collision::setSector(vector<model*> sector) {
	sector1 = sector;
}

vector<model*> Collision::getSector() {
	return sector1;
}

int Collision::ClassifyPoint( vector<float> vNorm, vector<float> pt, float distance, bool prt )
{
	float p = ColVector::dotProduct( vNorm, pt ) + distance;
	//cout<<"P "<<p<<endl;
    if( p > 0.0f ) {
		return 0;
	}
    else if( p < 0.0f ) {
		return 1;
	}
    return 2;
}

bool Collision::collisionTest(vector<float> startPoint,vector<float> direction) {
	updated = false;
	bool coll = false;
	vector<float> dest;
	dest.push_back(startPoint[0] + (direction[0]*6));
	dest.push_back(startPoint[1] + (direction[1]*6));
	dest.push_back(startPoint[2] + (direction[2]*6));
	int test = 0;
	for (int loop_m = 0; loop_m < sector1.size(); loop_m++) {
		if(sector1[loop_m]->getColl() == true && sel == false) {
			continue;
		}
		Output ot;
		if(ot.startsWith(sector1[loop_m]->getPolytype(),string("cylinder"))) {
			if(cylinderColl(sector1[loop_m],startPoint,direction) == false) {
				continue;
			}
			else {
				return true;
			}
		}
		else {
			for( int polyL = 0; polyL < sector1[loop_m]->display.getPolys().size() - 1; polyL++) {

				vector<float> vN1;
				vector<float> vN2;
			
				vector<float> p1;
				vector<float> p2;
				vector<float> p3;
				p1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getX());
				p1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getY());
				p1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getZ());
				p2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getX());
				p2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getY());
				p2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getZ());
				p3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getX());
				p3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getY());
				p3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getZ());

				//vN1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getX() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getX());
				//vN1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getY() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getY());
				//vN1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getZ() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getZ());

				//vN2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getX() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getX());
				//vN2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getY() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getY());
				//vN2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getZ() - sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getZ());

				//vNorm.push_back((vN1[1] * vN2[2]) - (vN1[2] * vN2[1]));
				//vNorm.push_back((vN1[2] * vN2[0]) - (vN1[0] * vN2[2]));
				//vNorm.push_back((vN1[0] * vN2[1]) - (vN1[1] * vN2[0]));

				//float magnitude = sqrt((vNorm[0]*vNorm[0]) + (vNorm[1]*vNorm[1]) + (vNorm[2]*vNorm[2]));
				//vNorm[0] = vNorm[0]/magnitude;
				//vNorm[1] = vNorm[1]/magnitude;
				//vNorm[2] = vNorm[2]/magnitude;

				//cout<<vNorm[0]<<" "<<vNorm[1]<<" "<<vNorm[2]<<endl;
				vNorm = sector1[loop_m]->display.getPolys()[polyL]->getNormal();
				float distance = ColVector::dotProduct(vNorm,p1);
				//if(ClassifyPoint(vNorm,startPoint,distance,false) == ClassifyPoint(vNorm,dest,distance,false)) {
				//	continue;
				//}
				vector<float> testing;
				testing.push_back(p1[0] - startPoint[0]);
				testing.push_back(p1[1] - startPoint[1]);
				testing.push_back(p1[2] - startPoint[2]);
				float top2 = ColVector::dotProduct(vNorm,testing);
				float top = -(ColVector::dotProduct(vNorm,startPoint) + distance);
				float bottom = ColVector::dotProduct(vNorm,direction);

				if(bottom < 0.00001 && bottom > -0.00001) {
					continue;
				}

				float t = top2/bottom;
				float nearest = floorf(t * 100 +  0.5) / 100;
				t = nearest;

				if(t>1 || t<0) {
					continue;
				}
				//cout<<"PASSED"<<endl;

				vector<float> rayXt;
				rayXt.push_back(direction[0] * t);
				rayXt.push_back(direction[1] * t);
				rayXt.push_back(direction[2] * t);
				intersect.clear();
				intersect.push_back(startPoint[0] + rayXt[0]);
				intersect.push_back(startPoint[1] + rayXt[1]);
				intersect.push_back(startPoint[2] + rayXt[2]);
				vector<float> v1;
				vector<float> v2;
				vector<float> v3;
				v1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getX() - intersect[0]);
				v1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getY() - intersect[1]);
				v1.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getZ() - intersect[2]);
				v2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getX() - intersect[0]);
				v2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getY() - intersect[1]);
				v2.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getZ() - intersect[2]);
				v3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getX() - intersect[0]);
				v3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getY() - intersect[1]);
				v3.push_back(sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getZ() - intersect[2]);

				float magnitude;
				magnitude = sqrtf((v1[0]*v1[0]) + (v1[1]*v1[1]) + (v1[2]*v1[2]));
				v1[0] = v1[0]/magnitude;
				v1[1] = v1[1]/magnitude;
				v1[2] = v1[2]/magnitude;
				magnitude = sqrtf((v2[0]*v2[0]) + (v2[1]*v2[1]) + (v2[2]*v2[2]));
				v2[0] = v2[0]/magnitude;
				v2[1] = v2[1]/magnitude;
				v2[2] = v2[2]/magnitude;
				magnitude = sqrtf((v3[0]*v3[0]) + (v3[1]*v3[1]) + (v3[2]*v3[2]));
				v3[0] = v3[0]/magnitude;
				v3[1] = v3[1]/magnitude;
				v3[2] = v3[2]/magnitude;
				vector<float> angles;
				angles.push_back(ColVector::dotProduct(v1, v2));
				angles.push_back(ColVector::dotProduct(v2, v3));
				angles.push_back(ColVector::dotProduct(v3, v1));
				for(int a=0;a<angles.size();a++) {
					if(angles[a] < -0.999) {
						angles[a] = -0.999;
					}
				}

				float thetaSum = acos(angles[0]) 
					 + acos(angles[1]) 
					 + acos(angles[2]);

				if (fabs(thetaSum - (2*PI)) < 0.3) {
					//cout<<"T "<<t<<endl;
					//cout<<"vNorm "<<vNorm[0]<<" "<<vNorm[1]<<" "<<vNorm[2]<<endl;
					//cout<<top2/bottom<<endl;
					//cout<<startPoint[0]<<" "<<startPoint[1]<<" "<<startPoint[2]<<endl;
					//cout<<direction[0]<<" "<<direction[1]<<" "<<direction[2]<<endl;
					//cout<<"POINT 1 = "<<sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getX()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getY()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(0).getZ()<<endl;
					//cout<<"POINT 2 = "<<sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getX()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getY()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(1).getZ()<<endl;
					//cout<<"POINT 3 = "<<sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getX()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getY()<< " "
					//				  <<sector1[loop_m]->display.getPolys()[polyL]->getVertex(2).getZ()<<endl;

					//cout<<acos(ColVector::dotProduct(v1, v2))<<endl;
					//cout<<acos(ColVector::dotProduct(v2, v3))<<endl;
					//cout<<acos(ColVector::dotProduct(v3, v1))<<endl;
					//cout<<v1[0]<<" "<<v1[1]<<" "<<v1[2]<<endl;
					//cout<<v2[0]<<" "<<v2[1]<<" "<<v2[2]<<endl;
					//cout<<v3[0]<<" "<<v3[1]<<" "<<v3[2]<<endl;
					//cout<<thetaSum<<endl;
					coll = true;
					//cout<<"COLLIDED"<<endl;
					if(sel == true && updated == false) {
						sector1[loop_m]->updateState();
						updated == true;
					}
				
					break;
				}
				else
					continue;
				}
				if(coll == true) {
					break;
				}

			}
	}
	updated = false;
	return coll;
}

float Collision::calculateHeight() {
	return intersect[1];
}

bool Collision::cylinderColl(model* mod,vector<float> start, vector<float> direction) {
	//direction = ColVector::divide(direction,5);
	vector<float> RC,cylPos;
	double cylRad;
	double d;
	double t,s;
	double lamda;
	vector<float> n,D,O;
	double ln;
	double in,out;
	start[1] = 0;
	cout<<"CYLINDER TEST"<<endl;
	cylPos.push_back(mod->display.getPolys()[0]->getVertex(0).getX());
	cylPos.push_back(mod->display.getPolys()[0]->getVertex(0).getY());
	cylPos.push_back(mod->display.getPolys()[0]->getVertex(0).getZ());
	cylRad = mod->display.getPolys()[0]->getVertex(1).getX();
	cout<<start[2]<<endl;
	RC = ColVector::subtract(start,cylPos);
	n = ColVector::crossProduct(direction,mod->getOVector());
	ln = ColVector::magnitude(n);
	if ( (ln<0.01)&&(ln>-0.01) ) return false;
	n = ColVector::unit(n,ln);
	cout<<"N "<< n[0]<<" "<<n[1]<<" "<<n[2]<<endl;
	d= fabs(ColVector::dotProduct(RC,n));
	cout<<" D "<<d<<" "<<cylRad<<endl;
    if (d<=cylRad) {
		cout<<"HMM"<<endl;
		O = ColVector::crossProduct(RC,mod->getOVector());
		t= -ColVector::dotProduct(O,n)/ln;
		O = ColVector::crossProduct(n,mod->getOVector());
		O = ColVector::unit(O,ColVector::magnitude(O));
		s = fabs( sqrt(cylRad*cylRad - d*d) / ColVector::dotProduct(direction,O));
		in=t-s;
		out=t+s;

		if (in<-0.01){
			if (out<-0.01) return false;
			else lamda=out;
		}
		else
        if (out<-0.01) {
			      lamda=in;
		}
		else
		if (in<out) lamda=in;
		else lamda=out;
		cout<<"LAMDA "<<lamda<<endl;
		if(lamda<=1) {
			return true;
		}

	}
	return false;
}