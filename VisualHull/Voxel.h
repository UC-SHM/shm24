/*
 * Voxel.h
 *
 *  Created on: 10 nov. 2020
 *      Author: sanchez
 */

#ifndef VOXEL_H_
#define VOXEL_H_
#include <iostream>

class Voxel {
public:
	short *binvoxMat;	// binvox orientd matrix
	int dimX;			// dimension X
	int dimY;			// dimension Y
	int dimZ;			// dimension Z
	bool saveBinvox(std::string fName);	// save binvox file

	Voxel(int dx, int dy, int dz);
	virtual ~Voxel();
};

#endif /* VOXEL_H_ */
