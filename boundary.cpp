	// Boundary class object is essentially a wall made up of a series of coordinates.
	// It coordinates are stored in x, y, and the number of coordinates is = to length

#include <stdlib.h>
#include <stdio.h>
#include "boundary.h"
#include "mathfunc.h"
#include "math.h"

const double pie = 3.14159;

// Boundary

Boundary::Boundary()
{

}
Boundary::Boundary(int inputlength)
{
	//Create empty Boundary
	x=new int [inputlength];
	z= new int[inputlength];
	length=inputlength;
}

Boundary::Boundary(int* bx,int* bz, int blength, char bside)
{
	// Takes values from the game and saves them to the boundary object
	
	length=blength;
	x=bx;
	z=bz;
	side=bside;
}

void Boundary::CreateBound(const Boundary &P, char cside, double width,char end)
{
	//Creates a boundary "width" away from boundary P on the side noted. 
	//If the end condition is given as 'c' it will close the boundary, otherwise the first and last points will be perpindicular to the original
	int count;//Counter used in "for" loops
	double w;//width
	double temp;
	double h,f,x0,z0,x1,z1,x2,z2,e,d,l;
	//0,1,2 denote the node index: 0:previous, 1:current, 2:next
	//h:angle of 1:2, -f:angle of 0:1, e:angle perpindicular to 0:1,
	//d:angle between e and the new node, l:distance between new and old node
	side=cside; //Save side
	if(side=='r'||side=='rr')//Depending on the side, move in or out from the original path
		w=width;
	else if(side=='l'||side=='ll')
		w=-width;
	for(count=0;count<P.length;count++)	
	{
		//Create a node for every node in the original element
		z1=(double)P.z[count];
		x1=(double)P.x[count];
		
		if(count==P.length-1)
		{
			//At the last node 
			z0=P.z[count-1];
			x0=P.x[count-1];
			h=FormAng(TrueAng(x0,x1,z0,z1),360);
			f=FormAng(TrueAng(x1,x0,z1,z0),0);
		}			
		else if(count==0)
		{
			//At the first node
			z2=P.z[count+1];
			x2=P.x[count+1];
			h=FormAng(TrueAng(x1,x2,z1,z2),360);
			f=FormAng(TrueAng(x2,x1,z2,z1),0);
		}
		else
		{
			//At all other nodes
			z2=P.z[count+1];
			x2=P.x[count+1];
			z0=P.z[count-1];
			x0=P.x[count-1];
			f=TrueAng(x1,x0,z1,z0);
			h=TrueAng(x1,x2,z1,z2);
		}
		//Trig to find the new position
		e=90+f;
		d=(h-f)/2-90;
		l=w/cos(d*pie/180);
		x[count]=(int)(x1+cos(FormAng(e+d,360)*pie/180)*l);
		z[count]=(int)(z1-sin(FormAng(e+d,360)*pie/180)*l);
	}
	if(end=='c'||end=='C')
	{
		//If it is supposed to be closed
		x[P.length-1]=x[0];
		z[P.length-1]=z[0];
	}
	for(count=0;count<P.length-1;count++)	// Check the boundary for kinks (only works for z kinks at the moment)
	{
		if(z[count]>z[count+1])
		{
			temp=z[count+1];
			z[count+1]=z[count];
			z[count]=temp;
		}
	}
}

int BetweenBounds(const Boundary &BL,const Boundary &BR, double x, double z)
{
	// Function that returns a 1 if a point is in between two boundaries of equal length
	// Note: this function only works for similar boundaries (Otherwise, strange overlapping occurs in the checking function)
	int count;//THe math behind this will be explained in Player.DetectBoundary() function
	double x1,x2,x3,x4,z1,z2,z3,z4;
	double m1,m2,m3,m4;
	double line1,line2,line3,line4;
	double included=0;
	for(count=0;count<=BR.length-2;count++)	// Check the location for every section in the boundary
	{
		x1=BL.x[count];
		z1=BL.z[count];
		x2=BR.x[count];
		z2=BR.z[count];
		x3=BR.x[count+1];
		z3=BR.z[count+1];
		x4=BL.x[count+1];
		z4=BL.z[count+1];
	
		m1=((x1-x2)/(z1-z2));
		m2=((x2-x3)/(z2-z3));
		m3=((x3-x4)/(z3-z4));
		m4=((x4-x1)/(z4-z1));

		line1=m1*(z-z1)+x1;
		line2=m2*(z-z2)+x2;
		line3=m3*(z-z3)+x3;
		line4=m4*(z-z4)+x4;
	
		if( ((x>line3&&x<line1&&(m3>0&&m1>0))||
			(x>line3&&x>line1&&(m3>0&&m1<0))||
			(x<line3&&x<line1&&(m3<0&&m1>0))||
			(x<line3&&x>line1&&(m3<0&&m1<0)))&&
			((line2<line4&&x>line2&&x<line4)||
			(line2>line4&&x<line2&&x>line4)))
				included=1;
	}
	if(included==1)
		return 1;
	else 
		return 0;
}