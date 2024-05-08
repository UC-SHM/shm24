/*
 * Imagen_test.cpp
 *
 *  Created on: 4 dic. 2021
 *      Author: sanchez
 */

#include "../Imagen.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <gtest/gtest.h>
using namespace std;

// file test definitions
static string imgFile="./test/imgTest.png";
static string filetext1="./test/imgTest.txt";
static string filetext2="./test/imgTestGold.txt";
//////

TEST(Imagen, loadImage) {
	Imagen img;

	ASSERT_TRUE(img.isEmptly());
	ASSERT_TRUE(img.load(imgFile));
	ASSERT_FALSE(img.isEmptly());
	ASSERT_EQ(img.width,640);
	ASSERT_EQ(img.height,480);
	ASSERT_EQ(img.channels,3);
}

TEST(Imagen, displayImage) {
	Imagen img;

	ASSERT_TRUE(img.load(imgFile));
	ASSERT_TRUE(img.display());
	std::cout << " Show image during 1 second" << std::endl;
	cimg_library::cimg::sleep(1000);
	ASSERT_TRUE(img.closeDisplay());
	std::cout << " Image closed!" << std::endl << " Wait 1 second" << std::endl;
	cimg_library::cimg::sleep(1000);
}


TEST(Imagen, copyImage) {
	Imagen img;
	Imagen imgCopy(640,480,1);

	ASSERT_TRUE(img.load(imgFile));

	// copy image
	memcpy(imgCopy.data,img.data,640*480);
	ASSERT_TRUE(imgCopy.display());
	std::cout << " Show gray image during 1 second" << std::endl;
	cimg_library::cimg::sleep(1000);
	ASSERT_TRUE(imgCopy.closeDisplay());
	std::cout << " Image gray closed!" << std::endl << " Wait 1 second" << std::endl;
	cimg_library::cimg::sleep(1000);
}

#include "../config.h"
using namespace std;
bool isFilesEqual(string& lFilePath, string& rFilePath);

TEST(Imagen, checkPixel) {
	Imagen img;
	ofstream outfile(filetext1);

	ASSERT_TRUE(outfile.is_open());

	ASSERT_TRUE(img.load(imgFile));
	ASSERT_EQ(img.width,W);
	ASSERT_EQ(img.height,H);
	for(int ph=0;ph<H;ph++){
		for(int pw=0;pw<W;pw++) {
			if(PIXEL(img.data,pw,ph) > 0) {
				outfile << "1";
			} else {
				outfile << "0";
			}
		}
		outfile << endl;
	}
	outfile.close();
	ASSERT_TRUE(isFilesEqual(filetext1,filetext2));
}
