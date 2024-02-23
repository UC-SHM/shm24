/*
 * Complex_test.cpp
 *
 *  Created on: 1 oct. 2020
 *      Author: sanchez
 */

#include "../Complex.h"
#include <iostream>
#include <gtest/gtest.h>	// DEfiniciones de google test
#include <gmock/gmock.h>
#include <ctime>

using namespace std;

TEST(Comples, assignacion) {
	Complex c1(8,9);
	Complex c2;
	clock_t  t1,t2;

	t1=clock();
	float r,i;
	c1.get(r,i);
	ASSERT_FLOAT_EQ(r,8);
	ASSERT_FLOAT_EQ(i,9);

	c2.get(r,i);
	ASSERT_FLOAT_EQ(r,0);
	ASSERT_FLOAT_EQ(i,0);
	Complex rCorrec(0,0);
//	ASSERT_EQ(c2,rCorrec);

	c2.set(10.0,11.1);
	c2.get(r,i);
	ASSERT_FLOAT_EQ(r,10.0);
	ASSERT_FLOAT_EQ(i,11.1);
	t2 = clock()-t1;
	cout << "Execution time: " << (float)t2/(float)(CLOCKS_PER_SEC ) << " " << t1 << "  " << t2 << endl;
}

TEST(Comples, suma) {
	Complex c1(8,9);
	Complex c2(10,20);
	Complex result;

	result=c1+c2;
	float r,i;
	result.get(r,i);
	ASSERT_FLOAT_EQ(r,18);
	ASSERT_FLOAT_EQ(i,29);
}
