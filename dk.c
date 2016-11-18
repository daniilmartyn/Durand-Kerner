#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#ifndef M_TWOPI
#define M_PI		3.14159265358979323846
#define M_TWOPI         (M_PI * 2.0)
#endif

#define MAXN 25 // max degree
#define E 10E-6 // relative error

complex double myMax(complex double c[], int n){

	double maxNum = cabs(c[0]);
	for(int i=1; i<n; i++){ 		// loop won't reach n, but we don't need n
		double temp = cabs(c[i]);
		if(maxNum < temp){
			maxNum = temp;
		}
	}
	return maxNum;
}

void initialValues(complex double c[], complex double z[], int n){ // compute initial roots

	complex double R = 1 + myMax(c, n);
	
	for(int j = 0; j < n; j++){
		
		double theta = j*(M_TWOPI)/n;
		z[j] = (cos(theta) + sin(theta)*I)*R;
	}
}

complex double polyfunc(complex double x, complex double c[], int n){ // plug in x value into polynomial and solve
	complex double result = c[n];
	for(int i = n-1; i >= 0; i--){
		result = c[i] + x*result;
	}
	return result;
}

void printRoots(complex double z[], int iter, int n){
	
	printf("iter %d\n", iter);
	for(int i = 0; i<n; i++){
		printf("z[%d] = %0.10f + %0.10f i\n", i, creal(z[i]), cimag(z[i]));
	}
}

int main(void) {
  int n = 0;  // polynomial degree 
  complex double c[MAXN+1];  // the coefficients from input
  complex double z[MAXN+1]; // roots of polynomial
  complex double deltaZ[MAXN+1];
  double a, b;
  while (scanf("%lf %lf", &a, &b) == 2)
    c[n++] = a + b*I;
  c[n] = 1;  // leading coeff implied
#ifdef REGURGITATE  // test input
  for (int i = 0; i < n; i++) {
    a = creal(c[i]);
    b = cimag(c[i]);
    printf("%0.10f + %0.10f i\n", a, b);
  }
#endif

  initialValues(c, z, n); // initial roots stored in z[]
  
#ifdef INITIAL  // print initial values
  for (int i = 0; i < n; i++) {
    a = creal(z[i]);
    b = cimag(z[i]);
    printf("%0.10f + %0.10f i\n", a, b);
  }
#endif

  for(int k = 1; k<50; k++){ // cap at 50 iterations
  
	printRoots(z,k,n);
	
	double deltaZmax = 0;
	
	for(int j=0; j<n; j++){
		double complex Q = 1 + 0*I;
		for(int i = 0; i < n; i++){
			if(i != j)
				Q *= (z[j]-z[i]);
		}
		
		deltaZ[j] = -1* polyfunc(z[j], c, n) /Q;
		double d = cabs(deltaZ[j]);
		if( d > deltaZmax)
			deltaZmax = d;	
	}
	
	for(int j=0; j<n; j++){
		z[j] += deltaZ[j];
	}
	
	if(deltaZmax <= E) // desired precision reached, stop iterating 
		break;
  }
  
  return 0;
}