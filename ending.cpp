//This brings up the end menu for the game

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "ending.h"

const double YsPi=3.1415927;

void Ending::Initialize (void)
{
	FsGetWindowSize (windowWid, windowHei);
}

void Ending::DrawLogo (double x, double y)
{
	glColor3ub(100, 100, 100);
	glBegin (GL_LINE_STRIP);

	glVertex2d (x+15, y-30);
	glVertex2d (x+15, y);
	glVertex2d (x, y);
	glVertex2d (x, y-15);
	glVertex2d (x+30, y-15);

	glEnd();

	FsSwapBuffers();
	FsSleep (10);
}

void Ending::DrawCreditList (void)
{
	FsGetWindowSize (windowWid, windowHei);
	if (YSOK==png.Decode("fishing.png"))
	{
		png.Flip();
		glRasterPos2d (0.0, (double)(windowHei-1));
		glDrawPixels (png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	}

	glColor3ub(100, 255, 0);
	glRasterPos2d(209-50,221);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(211-50,221);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(209-50,219);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(211-50,221);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(208-50,220);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(212-50,220);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(210-50,218);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(210-50,222);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");

	glColor3ub(0, 0, 0);
	glRasterPos2d(210-50,220);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(209-50,220);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(211-50,220);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(210-50,219);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");
	glRasterPos2d(210-50,221);
    YsGlDrawFontBitmap20x32 ("G A M E  O V E R");

	glColor3ub(255, 255, 255);
    glRasterPos2d(600,410);
    YsGlDrawFontBitmap8x12 ("Ting-Hao Chen");
	glRasterPos2d(600,430);
    YsGlDrawFontBitmap8x12 ("Samuel Dyment");
	glRasterPos2d(600,450);
    YsGlDrawFontBitmap8x12 ("Michael Lin");
	glRasterPos2d(600,470);
    YsGlDrawFontBitmap8x12 ("Ching-Heng Lu");
	glRasterPos2d(600,490);
    YsGlDrawFontBitmap8x12 ("Yi-Tsen Pan");
	glRasterPos2d(600,510);
    YsGlDrawFontBitmap8x12 ("Gaurav Verma");
	glRasterPos2d(600,530);
    YsGlDrawFontBitmap8x12 ("Jackie Yang");

	FsSwapBuffers();
	FsSleep (10);
}

