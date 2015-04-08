// This class allows for movement, drawing, and state of the hook

#ifndef HOOK_CLASS_H_IS_INCLUDED
#define HOOK_CLASS_H_IS_INCLUDED

#include "obstacle.h"
#include "button.h"

class Hook:public Obstacle
{
protected:
	int moving;		//0 = Deployed, 1 = reeling in fish
	int direction;		// 0 = up, 1 = down
	int steps;			//Keeps track of steps of the animation
	double hookSpeed;
public:
	Hook();

	void CleanUp(void);
	void draw();
	void animate();
	void catchFish();
	void stopCatch();
	int caughtOrNot(void);
};

#endif