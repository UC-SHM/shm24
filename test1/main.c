#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel
	{
	printf("Hola mundo\n");
	}
	return 0;
}
