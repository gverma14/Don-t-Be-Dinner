//General class that contains coordinate, size, and other parameters

#ifndef OBSTACLE_CLASS_H_IS_INCLUDED
#define OBSTACLE_CLASS_H_IS_INCLUDED

class Obstacle
{
protected:
	double x,y,z;				//Position (x,y,z)
	double xdim,ydim,zdim;		//Dimensions of influence volume
	double angle;				//Angle of rotation

public:
	Obstacle();
	Obstacle(double x, double y, double z, double xdim, double ydim, double zdim, double ang);
	//~Obstacle();
	
	double x0, y0, z0;
	void CleanUp(void);
	void setPosition(double x, double y, double z);
	void setSize(double xdim, double ydim, double zdim);
	void setAngle(double ang);


	double getX(void);
	double getY(void);
	double getZ(void);
	void getPosition(double &x, double &y, double &z);
	void getSize(double &xdim, double &ydim, double &zdim);
	void getAngle(double &angle);
	double getRadius();
};

#endif