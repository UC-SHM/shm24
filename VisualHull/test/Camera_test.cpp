/*
 * Camera_test.cpp
 *
 *  Created on: 4 dic 2021
 *      Author: sanchez
 */

#include "../Camera.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <gtest/gtest.h>
using namespace std;

string calFile="./test/CalMatrix.dat";

TEST(Camera, loadMatrix) {
	Camera cam;
	float cal[12]={
			   7.2782818255600000e+02  ,  -3.7933637427200000e+02  ,  -1.6000000000000000e+02  ,   1.5841278528486137e+03 ,
			  -1.3104874713600000e+02  ,  -1.2108983755200002e+02  ,  -7.8904588170000000e+02  ,   1.7366200465885913e+03 ,
			   6.3606499999999999e-01  ,   5.8772599999999997e-01  ,  -5.0000000000000000e-01  ,   4.9433611682300000e+00

	};

	ASSERT_TRUE(cam.loadProyMatrix(calFile));
	for(int i=0;i<12;i++) {
		ASSERT_FLOAT_EQ(cal[i],cam.proyMatrix[i]);
	}
}
