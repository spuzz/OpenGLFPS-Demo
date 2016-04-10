#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

Output::Output() {
	//pfile =  fopen("C:/Data/Visual Studio 2010/Projects/ogl/Data/output.txt","a");
}

Output::Output(string filename) {
	//pfile =  fopen(filename.c_str(),"a");
}

void Output::erase() {
	pfile = fopen("C:/Data/Visual Studio 2010/Projects/ogl/Data/output.txt","w");
	fputs ("ERASED \n" , pfile);
	fclose(pfile);
}

void  Output::out(string str) {
	myfile << str + " \n";
	pfile =  fopen("C:/Data/Visual Studio 2010/Projects/ogl/Data/output.txt","a");
	fputs(str.c_str(), pfile);
	fputs("\n", pfile);
	fclose(pfile);

}

void Output::out(float fl) {
	pfile =  fopen("C:/Data/Visual Studio 2010/Projects/ogl/Data/output.txt","a");
	stringstream ss (stringstream::in | stringstream::out);
	ss << fl;
	char output [255];
	string test = ss.str();
	fputs(test.c_str(), pfile);
	fputs("\n", pfile);
	fclose(pfile);

}

void Output::close() {
	//fclose(pfile);
}

