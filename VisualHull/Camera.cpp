/*
 * Camera.cpp
 *
 *  Created on: 4 dic 2021
 *      Author: sanchez
 */

#include "Camera.h"
#include <iostream>
#include <fstream>
using namespace std;

Camera::Camera() {
	// TODO Auto-generated constructor stub
}


bool Camera::loadProyMatrix(std::string name) {
	string token;
	ifstream infile(name.c_str());

	if(infile.is_open()==false) {
		cout << "Cannot open file " << name << endl;
		return false;
	}

	while( (infile >> token) && (token!=string("[Projection")));

	if(token==string("[Projection")) {
		infile >> token;
		for(int i=0; i<12; i++){
			infile >> proyMatrix[i];
		}
	} else {
		cout << "Cannot find  [Projection in file " << name << endl;
		return false;
	}
	return true;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

