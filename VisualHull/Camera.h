/*
 * Camera.h
 *
 *  Created on: 4 dic 2021
 *      Author: sanchez
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "Imagen.h"

class Camera {
public:
	Imagen img;				// Captured image
	float proyMatrix[12];	// Projection matrix

	bool loadProyMatrix(std::string name);
	Camera();
	virtual ~Camera();
};

#endif /* CAMERA_H_ */
