// This class makes the drawing and inputs for the menus at start


#include "menu.h"
#include "fssimplewindow.h"
#include <stdio.h>
#include <stdlib.h>
#include "ysglfontdata.h"
#include "yspng.h"
#include <time.h>



void GameMenu::Initialize (void)
{
	FsGetWindowSize (windowWid, windowHei);
}

void GameMenu::DrawBackground (void)
{
	if (YSOK==png.Decode("ocean.png"))
	{
		png.Flip();
		glRasterPos2d (0.0, (double)(windowHei-1));
		glDrawPixels (png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	}

	//enable transparent
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glColor4ub(80, 0, 0, 150);
	glBegin(GL_QUADS);

	glVertex2d (220.0,375.0);
	glVertex2d (580.0,375.0);
	glVertex2d (580.0,540.0);
	glVertex2d (220.0,540.0);

	glEnd();
	glDisable(GL_BLEND);
}
	
void GameMenu::DrawObjects (void)
{
	//fishing rod
	glColor3ub(125, 54, 3);
	glBegin(GL_QUADS);

	glVertex2d(785.0, 480.0);
	glVertex2d(770.0, 485.0);
	glVertex2d(625.0, 310.0);
	glVertex2d(632.0, 293.0);

	glVertex2d(632.0, 293.0);
	glVertex2d(625.0, 310.0);
	glVertex2d(480.0, 178.0);
	glVertex2d(486.0, 168.0);

	glVertex2d(486.0, 168.0);
	glVertex2d(480.0, 178.0);
	glVertex2d(340.0, 104.0);
	glVertex2d(338.0, 86.0);

	glVertex2d(338.0, 86.0);
	glVertex2d(340.0, 104.0);
	glVertex2d(206.0, 67.0);
	glVertex2d(183.0, 52.0);

	glEnd();

	//string
	glColor3ub(50, 50, 50);
	glBegin(GL_LINE_STRIP);

	glVertex2d(185.0, 57.0);
	glVertex2d(144.0, 119.0);
	glVertex2d(114.0, 197.0);
	glVertex2d(95.0, 279.0);

	glEnd();

	//hook
	glColor3ub(169, 169, 0);
	glBegin(GL_QUADS);

	glVertex2d(90.0, 279.0);
	glVertex2d(100.0, 279.0);
	glVertex2d(102.0, 327.0);
	glVertex2d(89.0, 337.0);

	glVertex2d(89.0, 337.0);
	glVertex2d(102.0, 327.0);
	glVertex2d(116.0, 346.0);
	glVertex2d(116.0, 363.0);

	glVertex2d(116.0, 363.0);
	glVertex2d(116.0, 346.0);
	glVertex2d(121.0, 341.0);
	glVertex2d(132.0, 342.0);

	glVertex2d(132.0, 342.0);
	glVertex2d(121.0, 341.0);
	glVertex2d(123.0, 328.0);
	glVertex2d(133.0, 328.0);

	glEnd();
}

void GameMenu::DrawWelcomeText (void)
{
	glColor3ub(100, 255, 0);
	glRasterPos2d(159,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(159,319);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(158,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(162,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,318);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,322);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");

	glColor3ub(0, 0, 0);
    glRasterPos2d(160,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(159,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(161,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(160,249);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(160,251);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");

	glRasterPos2d(160,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(159,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,319);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");


	glColor3ub(255, 125, 40);
    glRasterPos2d(260,420);
    YsGlDrawFontBitmap20x28 ("S:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(310,420);
    YsGlDrawFontBitmap16x20 ("1 Player");

	glColor3ub(255, 125, 40);
    glRasterPos2d(260,470);
    YsGlDrawFontBitmap20x28 ("M:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(310,470);
    YsGlDrawFontBitmap16x20 ("2 Player");

	glColor3ub(255, 125, 40);
    glRasterPos2d(260,520);
    YsGlDrawFontBitmap16x24 ("Esc:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(340,520);
    YsGlDrawFontBitmap16x20 ("end the game");

	glColor3ub(255, 255, 255);
    glRasterPos2d(520,25);
    YsGlDrawFontBitmap6x10 ("24-780 Engineering Computation Final Project");
	glRasterPos2d(600,45);
    YsGlDrawFontBitmap6x10 ("Copyright 2011 Fall");
}

void GameMenu::DrawKeyOption (void)
{
	glColor3ub(100, 255, 0);
	glRasterPos2d(159,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(159,319);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(158,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(162,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,318);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,322);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");

	glColor3ub(0, 0, 0);
    glRasterPos2d(160,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(159,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(161,250);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(160,249);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");
	glRasterPos2d(160,251);
    YsGlDrawFontBitmap20x32 ("D O N'T  b e");

	glRasterPos2d(160,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(159,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(161,320);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,319);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");
	glRasterPos2d(160,321);
    YsGlDrawFontBitmap20x32 ("       D I N N E R");


	glColor3ub(255, 125, 40);
    glRasterPos2d(260,420);
    YsGlDrawFontBitmap20x28 ("D:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(310,420);
    YsGlDrawFontBitmap16x20 ("Default Control");

	glColor3ub(255, 125, 40);
    glRasterPos2d(260,470);
    YsGlDrawFontBitmap20x28 ("R:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(310,470);
    YsGlDrawFontBitmap16x20 ("Remapped Control");

	glColor3ub(255, 125, 40);
    glRasterPos2d(260,520);
    YsGlDrawFontBitmap16x24 ("Esc:");
	glColor3ub(255, 255, 40);
    glRasterPos2d(340,520);
    YsGlDrawFontBitmap16x20 ("end the game");

	glColor3ub(255, 255, 255);
    glRasterPos2d(520,25);
    YsGlDrawFontBitmap6x10 ("24-780 Engineering Computation Final Project");
	glRasterPos2d(600,45);
    YsGlDrawFontBitmap6x10 ("Copyright 2011 Fall");
}

void GameMenu::DrawLogo (double x, double y)
{
	glColor3ub(100, 100, 100);
	glBegin (GL_LINE_STRIP);

	glVertex2d (x+15, y-30);
	glVertex2d (x+15, y);
	glVertex2d (x, y);
	glVertex2d (x, y-15);
	glVertex2d (x+30, y-15);

	glEnd();

}

void GameMenu::RunGameMenu(void)
{
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }
    
    key=FSKEY_NULL;
    for(;;)
    {
        FsPollDevice();
        key=FsInkey();
        
        if(key==FSKEY_ESC || key==FSKEY_D || key==FSKEY_R)
        {
            return;
        }
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        DrawBackground();
		DrawObjects();
		DrawKeyOption();
		DrawLogo(25, 575);
        
        FsSwapBuffers();
        FsSleep(20);
    }
}


void GameMenu::RunGameMenu2(void)
{
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }
    
    key=FSKEY_NULL;
    for(;;)
    {
        FsPollDevice();
        key=FsInkey();
        
        if(key==FSKEY_ESC || key==FSKEY_S || key==FSKEY_M)
        {
            return;
        }
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        Initialize();
		DrawBackground();
		DrawObjects();
		DrawWelcomeText();
		DrawLogo(25, 575);
        
        FsSwapBuffers();
        FsSleep(20);
    }
}


void GameMenu::DrawStart(double begin)
{
		
    
        glColor3ub(0,0,0);
        glRasterPos2d((windowWid/2)-90,(windowHei/2)-16);
        YsGlDrawFontBitmap20x32("S T A R T");
        
    
}


