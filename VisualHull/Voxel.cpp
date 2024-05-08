/*
 * Voxel.cpp
 *
 *  Created on: 10 nov. 2020
 *      Author: sanchez
 */

#include "Voxel.h"
#include <iostream>
#include <fstream>
using namespace std;

Voxel::Voxel(int dx, int dy, int dz) {
	binvoxMat=new short[dx*dy*dz];
	dimX=dx;
	dimY=dy;
	dimZ=dz;
}

bool Voxel::saveBinvox(std::string fName) {
	ofstream sal(fName, ios::out | ios::binary);
	char *buf;

	if(!sal.is_open()) {
		cout << "Cannot open " << fName << endl;
		return false;
	}
	buf=(char *) binvoxMat;
	long size=dimX*dimY*dimZ*sizeof(short);

	sal << "#binvox 1" << endl << "dim ";
	sal << dimX << " " << dimY << " " << dimZ << endl;
	sal << "data" << endl;
	if(!sal.write(buf,size)) {
		cout << "Cannot write binvox file: " << fName << endl;
		return false;
	}
	return true;
}

Voxel::~Voxel() {
	delete [] binvoxMat;
}

