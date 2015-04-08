// This defines self defined math function used in the game


#include <math.h>
#include "mathfunc.h"

const double pie = 3.14159;

//Math Functions

double TrueDist(double x1, double x2, double z1, double z2)
{
	//Calculates the distance between two points
	return sqrt((x1-x2)*(x1-x2)+(z1-z2)*(z1-z2));
}

double FormAng(double ang,int max)
{
	// Format angle function takes in an angle and adjusts it so that it will be between +max and -360+max
	// Useful for making an angle between 360 <-> 0 or 180 <-> -180 or 0 <-> -360
	double alpha=ang;
	while(alpha>max||alpha<max-360)
	{
		if(alpha>max)
			alpha-=360;
		if(alpha<max-360)
			alpha+=360;
	}
	return alpha;
}

double TrueAng(double x1, double x2, double z1, double z2)
{
	// Calculates the angle between two points
	double alpha;
	alpha=atan(-(z1-z2)/(x1 - x2))/pie*180;// Calculate alpha
	if(x1-x2<0)
		alpha+=180;// Fixes arctan function
	return alpha;
}

