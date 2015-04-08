#ifndef BOUNDARY_DEFINED
#define BOUNDARY_DEFINED

class Boundary
{
	// Boundary class object is essentially a wall made up of a series of coordinates.
	// It coordinates are stored in x, y, and the number of coordinates is = to length
public:
	int *x,*z,length;
	char side; //Denotes what side the boundary is on, 'l': left, 'r':right, etc.
	
	Boundary();
	Boundary(int inputlength); //Creating without values
	Boundary(int *inputx,int *inputz, int inputlength, char inputside); //Creating with values
	
	void CreateBound(const Boundary &P, char side, double w,char end);//For filling in values
};

int BetweenBounds(const Boundary &BL,const Boundary &BR, double x, double z);

#endif