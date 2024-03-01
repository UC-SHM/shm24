/*
 * Complex.h
 *
 *  Created on: 1 oct. 2020
 *      Author: sanchez
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

template <class T>
class Complex {
//private:
	T real;	// parte real
	T img;	// parte imagiantia
public:
	T mod();
	void set(T vreal, T vimg);
	void get(T &vreal,T &vimg);

	Complex operator+( const Complex &rhs);		// Addition
	Complex operator*( const Complex &rhs);		// Product
	Complex &operator=( const Complex &rhs);	// Equal
	bool operator==( const Complex &rhs);
	Complex(T vreal, T vimg);
	Complex();

	virtual ~Complex();

};

#endif /* COMPLEX_H_ */
