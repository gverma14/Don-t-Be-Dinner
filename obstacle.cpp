//General class that contains coordinate, size, and other parameters


#include "obstacle.h"
#include <math.h>

Obstacle::Obstacle()
{
	CleanUp();
}

Obstacle::Obstacle(double x, double y, double z, double xdim, double ydim, double zdim, double ang)
{
	CleanUp();
	setPosition(x,y,z);
	setSize(xdim,ydim,zdim);
	setAngle(ang);
}

void Obstacle::CleanUp(void)
{
	x = 0;
	y = 1;
	z = 0;
	xdim = .5;
	ydim = 0;
	zdim = .75;
	angle = 0;
}

void Obstacle::setPosition(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Obstacle::setSize(double xdim, double ydim, double zdim)
{
	this->xdim = xdim;
	this->ydim = ydim;
	this->zdim = zdim;
}

void Obstacle::setAngle(double ang)
{
	angle = ang;
}

double Obstacle::getX(void)
{
	return x;
}

double Obstacle::getY(void)
{
	return y;
}

double Obstacle::getZ(void)
{
	return z;
}

void Obstacle::getPosition(double &x, double &y, double &z)
{
	x = this->x;
	y = this->y;
	z = this->z;
}

void Obstacle::getSize(double &xdim, double &ydim, double &zdim)
{
	xdim = this->xdim;
	ydim = this->ydim;
	zdim = this->zdim;
}

double Obstacle::getRadius()
{
	double radius = sqrt(xdim*xdim+zdim*zdim);
	//printf("%lf  Radiussssssssss\n", radius);
	return radius;
}

void Obstacle::getAngle(double &angle)
{
	angle = this->angle;
}