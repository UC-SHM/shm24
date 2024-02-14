/*
 * main.c
 *
 *  Created on: 7 oct. 2020
 *      Author: sanchez
 */


#include <stdio.h>
#include <omp.h>

int main() {
	int id;
	int num;
	int acc;

	num=omp_get_num_threads();
	printf("\n Numero de hilos = %d", num);
	id=-1;
	acc=0;
#pragma omp parallel firstprivate(id,num)
	{
		int temp;
		temp=acc;
		printf("\n valor id=%d",id);
		id=omp_get_thread_num();
		num=omp_get_num_threads();
		for(int i=0;i<1000;i++);
		printf("\n Hilo %d de %d\n", id,num);
		acc=temp+1;
	}
	printf("\n ac  = %d", acc);

	num=omp_get_num_threads();
	printf("\n Numero de hilos = %d", num);
	return 0;
}
