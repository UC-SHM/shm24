/*
 * Imagen.h
 *
 *  Created on: 4 nov. 2021
 *      Author: sanchez
 */

#ifndef IMAGEN_H_
#define IMAGEN_H_
#include <iostream>
#include "CImg.h"

class Imagen {
public:
	unsigned char *data; // Image pixel array
	int width;			 // number of columns
	int height;			// Number of rows
	int channels;		// Number of channels: 1=gray, 3 =rgb
	std::string lastImageName;		// last loaded file
	bool isDisp;

	bool load(std::string fname);	// load image from a png file. Return true is thereis not errors
	bool isEmptly();				// true if there is an image
	bool display();					// Show image
	bool closeDisplay();			// Close image
	Imagen();
	Imagen(int cols, int rows, int chan);
	virtual ~Imagen();

private:
	cimg_library::CImg<unsigned char> img;
	cimg_library::CImgDisplay disp;
};

#endif /* IMAGEN_H_ */
