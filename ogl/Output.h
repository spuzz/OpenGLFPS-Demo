#include <sstream>
#include <fstream>
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include <iostream>
#include <string>
#pragma once
using namespace std;
class Output {
	public:
		Output();
		Output(string filename);
		void erase();
		void out();
		void close();
		void out(string str);
		void out(float ftl);
		bool exist();
		bool startsWith(std::string& src, std::string& token){	return src.substr(0,token.length()) == token ;}
	private:
		ofstream myfile;
		FILE * pfile;
		Output & operator=(const Output &); // intentionally undefined
};