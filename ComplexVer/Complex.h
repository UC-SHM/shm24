/*
 * Complex.h
 *
 *  Created on: 1 oct. 2020
 *      Author: sanchez
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

class Complex {
//private:
	float real;	// parte real
	float img;	// parte imagiantia
public:
	float mod();
	void set(float vreal, float vimg);
	void get(float &vreal,float &vimg);

	Complex operator+( const Complex &rhs);		// Addition
	Complex operator*( const Complex &rhs);		// Product
	Complex &operator=( const Complex &rhs);	// Equal
	bool operator==( const Complex &rhs);
	Complex(float vreal, float vimg);
	Complex();

	virtual ~Complex();

};

#endif /* COMPLEX_H_ */
