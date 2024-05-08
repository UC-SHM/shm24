/*
 * Voxel_test.cpp
 *
 *  Created on: 10 dic. 2020
 *      Author: sanchez
 */

#include "../Voxel.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>

#include <CImg.h>

using namespace std;

#include "config.h"
string fvoxtest="./test/genTestVox.binvox";
string cmdvoxtest=".\\viewbox\\viewvox.exe .\\test\\genTestVox.binvox";


TEST(Voxel, voxelTest1) {
	Voxel vox(XVOXEL,YVOXEL,ZVOXEL);
	bool flag;

	for(int x=0;x<XVOXEL;x++) {
		for(int y=0;y<YVOXEL;y++) {
			for(int z=0;z<ZVOXEL;z++) {
				flag=true;
				if(x<=XVOXEL/2 || x>=(3*XVOXEL/2))
					flag=false;
				if(y>=(3*YVOXEL/8) || y>=(5*YVOXEL/8))
					flag=false;
				if(z<=ZVOXEL/2 || z>=(32+ZVOXEL/2))
					flag=false;
				if(flag) {
					VOXEL(vox.binvoxMat,x,y,z)=VOXEL1;
				} else {
					VOXEL(vox.binvoxMat,x,y,z)=VOXEL0;
				}
			}
		}
	}
	ASSERT_TRUE(vox.saveBinvox(fvoxtest));
	cout << "pulse q para terminar" << endl;
	int status=system(cmdvoxtest.c_str());
	cimg_library::cimg::sleep(4000);
	ASSERT_EQ(status,1);
}
