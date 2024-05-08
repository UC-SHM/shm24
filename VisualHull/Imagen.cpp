/*
 * Imagen.cpp
 *
 *  Created on: 4 dic. 2021
 *      Author: sanchez
 */

#include "Imagen.h"


	bool Imagen::load(std::string fname) {	// load image from a png file. Return true is thereis not errors
		try {
			img.assign(fname.c_str());
			if(img.is_empty()) {
				return false;
			}
			width=img.width();
			height=img.height();
			channels=img.spectrum();
			data=img.data();
			lastImageName=fname;
			disp.assign(img, lastImageName.c_str(), 0, false, true);
			isDisp=true;
		}
		catch(cimg_library::CImgException & e){
			std::cout << "Error in Imagen::load(). error code: " << e.what() << std::endl;
			return false;
		}
		return true;
	}

	bool Imagen::isEmptly() { // true if there is an image

		return img.is_empty();
	}
	bool Imagen::display() {
		try {
			if(isDisp==false) {
				disp.assign(img, lastImageName.c_str(), 0, false, true);
				isDisp=true;
			}
			disp.show();
		}
		catch(cimg_library::CImgException & e){
			std::cout << "Error in Imagen::display(). error code: " << e.what() << std::endl;
			return false;
		}
		return true;
	}
	bool Imagen::closeDisplay(){
		try {
			disp.close();
		}
		catch(cimg_library::CImgException & e){
			std::cout << "Error in Imagen::closeDisplay(). error code: " << e.what() << std::endl;
			return false;
		}
		return true;
	}

	Imagen::Imagen(){ // Default constructor
		width=0;
		height=0;
		channels=0;
		lastImageName="No image";
		data=nullptr;
		isDisp=false;
	}

	Imagen::Imagen(int cols, int rows, int chan) {
		width=cols;
		height=rows;
		channels=chan;
		lastImageName="No image";
		img.assign(cols,rows,1,chan);
		data=img.data();
		isDisp=false;
	}

	Imagen::~Imagen(){

	}
