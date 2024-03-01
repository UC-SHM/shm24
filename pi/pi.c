/*
 * pi.c
 *
 *  Created on: 8 nov. 2018
 *      Author: sanchez
 */


/* Serial Code */
#include <stdio.h>
#include <omp.h>
#define CASO 5




static long num_steps = 1000000000;
double step;

#if CASO==1
int main ()
{
	int i;
	double x, pi, sum = 0.0;
	double tinit, tfin;

	tinit=omp_get_wtime();
	  step = 1.0/(double) num_steps;

	  for (i=1;i<= num_steps; i++){
		  x = (i-0.5)*step;
		  sum = sum + 4.0/(1.0+x*x);
	  }
	  pi = step * sum;

	  tfin=omp_get_wtime();
	  printf(" Pi = %le , Execution time= %le\n", pi, tfin-tinit);
	  return 0;
}

#endif

#if CASO==2

#define NUM_THREADS 4
int main ()
{

	int nthreads;
	double pi, sum[NUM_THREADS];
	double tinit, tfin;

	omp_set_num_threads(NUM_THREADS);
	tinit=omp_get_wtime();

	step = 1.0/(double) num_steps;

#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id=omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if(id==0)
			nthreads=nthrds;
	  for (i=id, sum[id]=0.0;i<= num_steps; i=i+nthrds){
		  x = (i-0.5)*step;
		  sum[id] = sum[id] + 4.0/(1.0+x*x);
	  }
	}
	int i;

	pi=0.0;
	for(i=0; i < nthreads;i++) {
	  pi += step * sum[i];
	}

	  tfin=omp_get_wtime();
	  printf(" Pi = %le , Execution time= %le\n", pi, tfin-tinit);
	  return 0;
}
#endif

#if CASO==3

#define NUM_THREADS 3
#define PAD 16
int main ()
{

	int nthreads;
	double pi, sum[NUM_THREADS][PAD];
	double tinit, tfin;

	omp_set_num_threads(NUM_THREADS);
	tinit=omp_get_wtime();

	step = 1.0/(double) num_steps;

#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id=omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if(id==0)
			nthreads=nthrds;
	  for (i=id, sum[id][0]=0.0;i<= num_steps; i=i+nthrds){
		  x = (i-0.5)*step;
		  sum[id][0] = sum[id][0] + 4.0/(1.0+x*x);
	  }
	}
	int i;

	pi=0.0;
	for(i=0; i < nthreads;i++) {
	  pi += step * sum[i][0];
	}

	  tfin=omp_get_wtime();
	  printf(" Pi = %le , Execution time= %le\n", pi, tfin-tinit);
	  return 0;
}
#endif

#if CASO==4

#define NUM_THREADS 4
int main ()
{

	//int nthreads;
	double pi;
	double tinit, tfin;

	omp_set_num_threads(NUM_THREADS);
	tinit=omp_get_wtime();

	step = 1.0/(double) num_steps;
	pi=0.0;

#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		double sum=0;

		id=omp_get_thread_num();
		nthrds = omp_get_num_threads();
		/*if(id==0)
			nthreads=nthrds; */
	  for (i=id;i<= num_steps; i=i+nthrds){
		  x = (i-0.5)*step;
		  sum = sum + 4.0/(1.0+x*x);
	  }
	  sum *= step;
#pragma omp atomic
	  pi += sum;
	}
	//int i;

	/*
	pi=0.0;
	for(i=0; i < nthreads;i++) {
	  pi += step * sum[i];
	} */

	  tfin=omp_get_wtime();
	  printf(" Pi = %le , Execution time= %le\n", pi, tfin-tinit);
	  return 0;
}
#endif

#if CASO==5
int main ()
{
	int i;
	double pi, sum = 0.0;
	double tinit, tfin;

	  tinit=omp_get_wtime();
	  step = 1.0/(double) num_steps;

	  sum=0.0;
#pragma omp parallel for reduction(+:sum)
	  for (i=1;i<= num_steps; i++){
		  double x;

		  x = (i-0.5)*step;
		  sum = sum + 4.0/(1.0+x*x);
	  }
	  pi = step * sum;

	  tfin=omp_get_wtime();
	  printf(" Pi = %le , Execution time= %le\n", pi, tfin-tinit);
	  return 0;
}

#endif
