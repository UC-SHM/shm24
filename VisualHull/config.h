/*
 * config.h
 *
 *  Created on: 8 nov. 2021
 *      Author: sanchez
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// image default values
#define W 640
#define H 480

// voxel array dimensions
#define XVOXEL 128
#define YVOXEL 128
#define ZVOXEL 128

// VOXEL values
#define VOXEL0 256
#define VOXEL1 257

// access to a pixel in the image array
#define PIXEL(ARRAY, X,Y)  ARRAY[(Y)*W+(X)]

// access to voxel in the voxel array
#define VOXEL(ARRAY, X,Y,Z)  ARRAY[(Z)+(ZVOXEL*(Y))+(ZVOXEL*YVOXEL*(X))]

// Calculate world coordinates from voxel position
#define XPOS(X) (((float)(2.0*(X)))/((float) XVOXEL))-1.0
#define YPOS(Y) (((float)(2.0*(Y)))/((float) YVOXEL))-1.0
#define ZPOS(Z) (((float)(2.0*(Z)))/((float) ZVOXEL))

#endif /* CONFIG_H_ */
