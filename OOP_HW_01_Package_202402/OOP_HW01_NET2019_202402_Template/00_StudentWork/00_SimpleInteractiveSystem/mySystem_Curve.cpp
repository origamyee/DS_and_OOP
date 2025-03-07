//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2024/03/03
//
#include "mySystem_Curve.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

//
// no-arg constructor
//
CURVE_FUNCTION::CURVE_FUNCTION()
{
	//xMin = -100.0;
	//xMax= 100.0;

	xMin = -100.0;
	xMax = 100.0;

	mNumSamples = 100;

	a = b = c = d = 1;
	a = 1.0;
	b = -0.5;

	mCurveType = CURVE_TYPE_EXPONENTIAL;
}

//
// set the curve type
//
void CURVE_FUNCTION::setCurveType(CURVE_TYPE type)
{
	//
	// implement your own stuff
	//
	mCurveType = type;
}

// increase parameter b
void CURVE_FUNCTION::increase(double dv)
{
	b += dv;
}

// decrease parameter b
void CURVE_FUNCTION::decrease(double dv)
{
	b -= dv;

}

// set the value to parameter c
void CURVE_FUNCTION::setC(double c)
{
	//
	// implement your own stuff
	//
	this->c = c;
}

// set the value to parameter d
void CURVE_FUNCTION::setD(double d)
{
	//
	// implement your own stuff
	//
	this->d = d;
}

// ask for input
void CURVE_FUNCTION::askForInput()
{
	//empty
}

//
// set the interval of x
// xMin <- min_X
// xMax <- max_X
//
void CURVE_FUNCTION::set_IntervalOfX(double min_X, int max_X)
{
	//
	// implement your own stuff
	//
	xMin = min_X;
	xMax = max_X;
}

//
// return the interval of x
// xMin <- this->xMin
// xMax <- this->xMax
void CURVE_FUNCTION::getIntervalOfX(double& xMin, double& xMax) const
{
	//
	// implement your own stuff
	//
	xMin = this->xMin;;
	xMax = this->xMax;
}

//
// return the number of sample points
//
int CURVE_FUNCTION::getNumOfSamples() const
{
	//
	// implement your own stuff
	//
	return mNumSamples;
}

//
// set the number of sample points
// mNumSamples <- num
//
void CURVE_FUNCTION::setNumOfSamplePoints(int num)
{
	//
	// implement your own stuff
	//
	mNumSamples = num;
}

//
// get the value of a function for x
//
double CURVE_FUNCTION::getValue(double x) const
{
	//
	// implement your own stuff
	//
	double y = 0;
	switch (mCurveType) {
	case CURVE_TYPE_EXPONENTIAL:
		y = (x / 2.5) / 10 - 1 + (c + sin(4 * d * (x / 2.5))) * exp(-(x / 2.5));
		break;
	case CURVE_TYPE_COSINE:
		y = c * x - d * x * cos(x);
		break;
	case CURVE_TYPE_QUADRATIC:
		y = x * x + c * x + d;
		break;
	}

	return y;
}

//
// randomly compute a value for c 
// inside the interval [u0, u1] in a uniform manner
//
void CURVE_FUNCTION::setRandom_C(double u0, double u1)
{
	c = (u1 - u0) * rand() / (RAND_MAX + 1.0) + u0;

}

//
// randomly compute a value for d 
// inside the interval [u0, u1] in a uniform manner
//
void CURVE_FUNCTION::setRandom_D(double u0, double u1)
{
	d = (u1 - u0) * rand() / (RAND_MAX + 1.0) + u0;
}

//
// get the boundary point (x, y)
// point_index = 0: return the leftmost point (x,y)
// point_index = 1: return the rightmost point (x,y)
// 
void CURVE_FUNCTION::getBoundaryPoint(int point_index, double& x, double& y) const
{
	//
	// implement your own stuff
	//
	x = xMin;
	y = -10;
	switch (point_index) {
	case 0:
		x = xMin;
		y = getValue(xMin);
		break;
	case 1:
		x = xMax;
		y = getValue(xMax);
		break;
	};
}

//
// get the x- and y-coordinates of all the extreme points 
//
// store the x- and y-coordinates to X and Y vectors, respectively
//
void CURVE_FUNCTION::getExtremePoints(vector<double>& X, vector<double>& Y) const
{
	X.clear();
	Y.clear();

	//
	// implement your own stuff
	//
	vector<double> tempX;
	vector<double> tempY;
	for (int i = 0; i < mNumSamples; i++) {
		tempX.push_back(xMin + i * (xMax - xMin) / (mNumSamples - 1));
		tempY.push_back(getValue(tempX[i]));
	}
	for (int i = 1; i < mNumSamples - 1; i++) {
		if (tempY[i] < tempY[i - 1] && tempY[i] < tempY[i + 1]) {
			X.push_back(tempX[i]);
			Y.push_back(tempY[i]);
		}
		if (tempY[i] > tempY[i - 1] && tempY[i] > tempY[i + 1]) {
			X.push_back(tempX[i]);
			Y.push_back(tempY[i]);
		}
	}

}