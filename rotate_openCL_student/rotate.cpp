// Funcion rotacion
/*
 * rotation.c
 *
 *
 *  Created on: 16 nov. 2016
 */
void img_rotate(float* dest_data,
                float* src_data,
                           int  W,
                           int  H,
                         float  sinTheta,
                         float  cosTheta,
                         int ix,
                         int iy
                         ) {
	float fx,fy;
	int nx,ny;
	int desx,desy;
	int trasx,trasy;
	trasx= W/2.0;
	trasy= H/2.0;
	desx=ix-trasx;
	desy=iy-trasy;
	// Transformacion afin: rotacion
	fx=cosTheta*desx + sinTheta*desy 					+ trasx;
	fy= 			   cosTheta*desy - (sinTheta*desx) 	+ trasy;

	// Interpolacion: vecino entero
	nx= (int)fx;
	ny= (int)fy;

	// Escribo
	if((ny>=0 && ny<H) && (nx>=0 && nx<W))
		dest_data[(iy*W)+ix]=src_data[(ny*W)+nx];
	else
		dest_data[(iy*W)+ix]=255;
}


