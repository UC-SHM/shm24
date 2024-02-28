/*
 * main.c
 *
 *  Created on: 16 feb 2024
 *      Author: sanchez
 */


#include <stdio.h>
int main() {
	int i=1;
//#pragma omp parallel
	printf(" Hola %i\n",i);
flush();
	return 0;
}
