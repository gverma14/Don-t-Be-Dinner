// This class makes the drawing and inputs for the menus at start

#ifndef MENU_DEFINED
#define MENU_DEFINED

#include "yspng.h"

class GameMenu
{
public:
	YsRawPngDecoder png;
	int key;
	int windowWid, windowHei;
	 char name[256];
	void Initialize (void);
	void SetObjectPosition (void);
	void DrawBackground (void);
	void DrawObjects (void);
	void DrawWelcomeText (void);
	void DrawKeyOption (void);
	void DrawLogo (double x, double y); //bottom-left point

	void RunGameMenu(void);
    void RunGameMenu2(void);
	void DrawStart(double begin);
  
};


#endif