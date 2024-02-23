/*
 * Complex.cpp
 *
 *  Created on: 1 oct. 2020
 *      Author: sanchez
 */

#include "Complex.h"
#include <cmath>
#include <iostream>

using namespace std;

// Module
float Complex::mod() {
		double mod;
		mod= (double)(real*real) + (double)(img*img);
		return ((float) sqrt( mod));
	}

// Set
void Complex::set(float vreal, float vimg) {
	real=vreal;
	img=vimg;
}

// Get
void Complex::get(float &vreal, float &vimg) {
	vreal=real;
	vimg=img;
}

// Constructor
Complex::Complex(float vreal, float vimg) {
		real=vreal;
		img=vimg;

	}


//default constructor
Complex::Complex() {
	real=0;
	img=0;
}

// Destructor
Complex::~Complex() {
	cout << "estoy en el destructor " << std::endl;
}

// Operador suma
Complex Complex::operator+( const Complex &rhs)	// Operador +
	{
	Complex result;

	result.real = this->real + rhs.real;
	result.img  = this->img  + rhs.img ;
	return result;
	}

// operador producto
Complex Complex::operator*( const Complex &rhs)	// Operador *
	{
	Complex result;

	result.real = (this->real*rhs.real)- (this->img *rhs.img );
	result.img  = (this->real*rhs.img) + (this->img *rhs.real);
	return result;
	}

// Asignacion
Complex &Complex::operator=(const Complex &rhs)	// Asignacion.
					// Cuidado! El operador this es el lhs.
{
	if(this == &rhs) {	// No se asigna el mismo valor
		return *this;
	}
	real=rhs.real;	// Copy values
	img=rhs.img;

	return *this;
}

bool Complex::operator==( const Complex &rhs) {
	bool ret;

	if(real==rhs.real && img==rhs.img) {
		ret=true;
	} else {
		ret=false;
	}
	return ret;
}
