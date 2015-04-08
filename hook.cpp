
// This class allows for movement, drawing, and state of the hook


#include <stdio.h>
#include "fssimplewindow.h"
#include "hook.h"
#include "button.h"

Hook::Hook()
{
	CleanUp();
}

void Hook::CleanUp(void)
{
	x = 0;
	y = 1;
	z = 0;
	
	angle = 0;
	moving = 0;
	int direction = 0;		// 0 = up, 1 = down
	int steps = 0;
	hookSpeed = .25;
}

void Hook::catchFish()
{
	/* Moves the hook up and down */
	moving = 1;
	//hookSpeed = .25;
}

void Hook::stopCatch()
{
	moving = 0;
}

void Hook::draw(void)
{
	
	//Enable for hook
	glColor3ub(50,50,50);
	glBegin(GL_QUADS);
	
	double xUnit = 0.25;
	double yUnit = 0.25;
	double zUnit = 0.125;
	double zmod = -z;
	//Draw Rim
	glVertex3d(x-xUnit,y,zmod+zUnit);
	glVertex3d(x-2*xUnit,y,zmod+zUnit);
	glVertex3d(x-2*xUnit,y,zmod-zUnit);
	glVertex3d(x-xUnit,y,zmod-zUnit);

	glVertex3d(x-2*xUnit,y,zmod+zUnit);
	glVertex3d(x-2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x-2*xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x-2*xUnit,y,zmod-zUnit);

	glVertex3d(x-xUnit,y,zmod+zUnit);
	glVertex3d(x-xUnit,y-yUnit,zmod+zUnit);
	glVertex3d(x-xUnit,y-yUnit,zmod-zUnit);
	glVertex3d(x-xUnit,y,zmod-zUnit);

	glVertex3d(x-xUnit,y-yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y-yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y-yUnit,zmod-zUnit);
	glVertex3d(x-xUnit,y-yUnit,zmod-zUnit);

	glVertex3d(x+xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y-yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y-yUnit,zmod-zUnit);
	glVertex3d(x+xUnit,y+2*yUnit,zmod-zUnit);

	glVertex3d(x+xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y+2*yUnit,zmod-zUnit);
	glVertex3d(x+xUnit,y+2*yUnit,zmod-zUnit);
	
	glVertex3d(x+2*xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x+2*xUnit,y+2*yUnit,zmod-zUnit);

	glVertex3d(x-2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x-2*xUnit,y-2*yUnit,zmod-zUnit);

	//Draw front face
	glVertex3d(x-xUnit,y,zmod+zUnit);
	glVertex3d(x-2*xUnit,y,zmod+zUnit);
	glVertex3d(x-2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x-xUnit,y-2*yUnit,zmod+zUnit);

	glVertex3d(x-xUnit,y-yUnit,zmod+zUnit);
	glVertex3d(x-xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-yUnit,zmod+zUnit);

	glVertex3d(x+2*xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y+2*yUnit,zmod+zUnit);
	glVertex3d(x+xUnit,y-2*yUnit,zmod+zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod+zUnit);

	//Draw back face
	glVertex3d(x-xUnit,y,zmod-zUnit);
	glVertex3d(x-2*xUnit,y,zmod-zUnit);
	glVertex3d(x-2*xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x-xUnit,y-2*yUnit,zmod-zUnit);

	glVertex3d(x-xUnit,y-yUnit,zmod-zUnit);
	glVertex3d(x-xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x+2*xUnit,y-yUnit,zmod-zUnit);

	glVertex3d(x+2*xUnit,y+2*yUnit,zmod-zUnit);
	glVertex3d(x+xUnit,y+2*yUnit,zmod-zUnit);
	glVertex3d(x+xUnit,y-2*yUnit,zmod-zUnit);
	glVertex3d(x+2*xUnit,y-2*yUnit,zmod-zUnit);

	glEnd();
	
	glColor3ub(0,0,0);
	glBegin(GL_LINES);
	glVertex3d(x+1.5*xUnit,y+2*yUnit,-z);
	glVertex3d(x+1.5*xUnit,12.5,-z);
	glEnd();

	//beacon
	//X-axis (red)
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(50,0,0);
	glEnd();

	//Y-axis (green)
	glColor3ub(0,255,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,50,0);
	glEnd();

	//zmod-axis (blue)
	glColor3ub(0,0,255);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,0,50);
	glEnd();

}

void Hook::animate()
{
		
	if(moving == 1)
	{

		y += hookSpeed;
		
		if (y >= 12.5 && hookSpeed > 0)
		{
			
			hookSpeed = -hookSpeed;
		}
		else if( y <=1 && hookSpeed <0)
		{
			moving = 0;
			hookSpeed = -hookSpeed;
		}

		//printf("x: %.2lf\t\ty: %.2lf\tz: %.2lf\t\tsteps: %d\n",getX(),getY(),getZ(),steps);
	}

	
}

int Hook::caughtOrNot(void)
{
	//If moving = 0, the hook has not caught anything and is not moving
	//If moving = 1, the hook has caught a fish and is moving

	return moving;
}