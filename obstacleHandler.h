// Handles the array of hooks, generates and maintains the array

#ifndef OBSHANDLER_CLASS_H_IS_INCLUDED
#define OBSHANDLER_CLASS_H_IS_INCLUDED

#include "hook.h"
#include "boundary.h"
#include "button.h"

class ObstacleHandler
{
protected:
	Hook arr[250];
	int arraySize;
	int hookYPos;

public:
	ObstacleHandler();

	void CleanUp(void);
	int generateHooks(int numHooks, const Boundary &Path, const Boundary &BL, const Boundary &BR);		//Randomly generates a field of hooks
	void draw();
	void animate();
	void setAllCaught();
	Hook* getHookArray();				//Returns the array of hooks
	int getArraySize();						//Returns the size of the array
	void resetAll();
};

#endif