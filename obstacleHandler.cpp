// Handles the array of hooks, generates and maintains the array


#include <stdio.h>
#include "obstacleHandler.h"
#include "boundary.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "button.h"

ObstacleHandler::ObstacleHandler()
{
	CleanUp();
}

void ObstacleHandler::CleanUp(void)
{
	arraySize = 0;
	hookYPos = 1;
}

int ObstacleHandler::generateHooks(int numHooks, const Boundary &Path, const Boundary &BL, const Boundary &BR)
{
	srand(time(NULL));
	//Returns 1 if successfully generates hooks, returns 0 otherwise
	if(numHooks > 250)
	{
		printf("numHooks must be less than 100");
		return 0;
	}

	double xtemp, ztemp;
	
	for(int i = 0; i < numHooks; i++)
	{
		Hook tempH;
		
		do{
			//Place the player, and see if it is between the two boundaries
			xtemp=Path.x[Path.length-1]*(double)(rand()%100)/100;	// create initial x coord
			ztemp=Path.z[Path.length-1]*(double)(rand()%100)/100;	// create initial z coordinate
		}while(0==BetweenBounds(BL,BR,(int)xtemp,(int)ztemp)||!(ztemp<Path.z[Path.length-4])||!(ztemp>Path.z[3]));

		
		//tempH.CleanUp();
		tempH.setPosition(xtemp, 1, ztemp);
		tempH.x0 = xtemp;
		tempH.z0 = ztemp;

		arr[i] = tempH;

		arraySize++;
	}
	return 1;
}

void ObstacleHandler::resetAll()
{
	for(int i = 0; i < getArraySize(); i++)
	{
		arr[i].stopCatch();
		arr[i].setPosition(arr[i].x0, 1, arr[i].z0);
	}
}

void ObstacleHandler::draw()
{
	for(int i = 0; i < arraySize; i++)
	{
		arr[i].draw();
	}
}

void ObstacleHandler::animate()
{
	for(int i = 0; i < arraySize; i++)
	{
		//arr[i].catchFish();		
		arr[i].animate();
	}
	
}

void ObstacleHandler::setAllCaught()
{
	for(int i = 0; i < arraySize; i++)
	{
		arr[i].catchFish();		
		
	}
}

	
Hook* ObstacleHandler::getHookArray()
{
	return arr;
}

int ObstacleHandler::getArraySize()
{
	return arraySize;
}