

// The Button class manages all the button inputs for the game, all of the buttons are mapped to specific variables 
// This ensures that specific players, or the game itself only can use these buttons
#include "button.h"
#include <stdio.h>
#include "fssimplewindow.h"
#include <stdlib.h>
#include "ysglfontdata.h"

#include "yspng.h"

Button::Button()
{
    Reset();
    Update();
}

Button::~Button()
{
    Reset();
}

void Button::DrawBackground (void)
{
	if (YSOK==png.Decode("fish1.png"))
	{
		png.Flip();
		glRasterPos2d (0.0, (double)(windowHei-1));
		glDrawPixels (png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	}
}

void Button::DrawModeTitle1 (void)
{
	glColor3ub(255, 255, 255);
    glRasterPos2d(80,100);
    YsGlDrawFontBitmap20x32 ("1 P");
	glRasterPos2d(79,100);
    YsGlDrawFontBitmap20x32 ("1 P");
	glRasterPos2d(81,100);
    YsGlDrawFontBitmap20x32 ("1 P");
	glRasterPos2d(80,99);
    YsGlDrawFontBitmap20x32 ("1 P");
	glRasterPos2d(80,101);
    YsGlDrawFontBitmap20x32 ("1 P");
}

void Button::DrawModeTitle2 (void)
{
	glColor3ub(255, 255, 255);
    glRasterPos2d(80,100);
    YsGlDrawFontBitmap20x32 ("2 P");
	glRasterPos2d(79,100);
    YsGlDrawFontBitmap20x32 ("2 P");
	glRasterPos2d(81,100);
    YsGlDrawFontBitmap20x32 ("2 P");
	glRasterPos2d(80,99);
    YsGlDrawFontBitmap20x32 ("2 P");
	glRasterPos2d(80,101);
    YsGlDrawFontBitmap20x32 ("2 P");
}

void Button::DrawKeyboardSetting (void)
{
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glColor4ub(0, 0, 0, 200);
	glBegin(GL_QUADS);

	glVertex2d (80.0,140.0);
	glVertex2d (580.0,140.0);
	glVertex2d (580.0,400.0);
	glVertex2d (80.0,400.0);

	glEnd();
	glDisable(GL_BLEND);
}

void Button::DrawLogo (double x, double y)
{
	glColor3ub(100, 100, 100);
	glBegin (GL_LINE_STRIP);

	glVertex2d (x+15, y-30);
	glVertex2d (x+15, y);
	glVertex2d (x, y);
	glVertex2d (x, y-15);
	glVertex2d (x+30, y-15);

	glEnd();

	//FsSwapBuffers();
	//FsSleep (10);
}

void Button::Reset()
{
	Initialize();
}

void Button::Default(void)
{
    
    SF1=FSKEY_UP;
    SB1=FSKEY_DOWN;
    SL1=FSKEY_LEFT;
    SR1=FSKEY_RIGHT;
    SU1=FSKEY_K;
    SD1=FSKEY_M;
    
}

void Button::Default2(void)
{
    
    SF2=FSKEY_W;
    SB2=FSKEY_S;
    SL2=FSKEY_A;
    SR2=FSKEY_D;
    SU2=FSKEY_R;
    SD2=FSKEY_F;
    
}

void Button::Player1Button()
{
	SF=SF1;
    SB=SB1;
    SL=SL1;
    SR=SR1;
    SU=SU1;
    SD=SD1;
}

void Button::Player2Button()
{
	SF=SF2;
    SB=SB2;
    SL=SL2;
    SR=SR2;
    SU=SU2;
    SD=SD2;
}


void Button::Initialize(void)
{
    SU=0,SD=0,SL=0,SR=0,SF=0,SB=0;
	SU1=0,SD1=0,SL1=0,SR1=0,SF1=0,SB1=0;
	SU2=0,SD2=0,SL2=0,SR2=0,SF2=0,SB2=0;
	GP = FSKEY_P;
	GC = FSKEY_C;
	GR = FSKEY_SPACE;
	G1 = FSKEY_0;
	G2 = FSKEY_1;
	pause=0, reset=0, cont=0, one=0, two=0;

    FsGetWindowSize (windowWid, windowHei);
}

int Button::checkGameControl(int key)
{
	if(key == GC || key == GP || key == GR || key == G1 || key == G2)
	{
		return 1;
	}
	else
		return 0;

}

void Button::Remap()
{
	FsGetWindowSize (windowWid, windowHei);
	printf("Mapped S1");
    FsClearEventQueue();
    
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }
   
	//Initialize();
    while(SF1==0 || checkGameControl(SF1))
    {   
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		DrawBackground();
		DrawModeTitle1();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (press key to remap)");

		DrawLogo(25, 575);

		SF1=FsInkey();
       FsSwapBuffers();
       FsSleep(20);
    }

    while(SB1==0 || checkGameControl(SB1))
    {    
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle1();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (press key to remap)");

		DrawLogo(25, 575);

        SB1=FsInkey();       
        FsSwapBuffers();
        FsSleep(20);
    }
    
  
    
    while(SL1==0 || checkGameControl(SL1))
    {        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle1();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Left : (press key to remap)");

		DrawLogo(25, 575);

		SL1=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }
    
    while(SR1==0  || checkGameControl(SR1))
    {        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle1();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Left : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Right : (press key to remap)");

		DrawLogo(25, 575);

        SR1=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }
	
    
}

void Button::Remap2()
{
    FsClearEventQueue();
    FsGetWindowSize (windowWid, windowHei);
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }

	//Initialize();
    
    while(SF2==0 || checkGameControl(SF2) )
    {   
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle2();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (press key to remap)");

		DrawLogo(25, 575);

        SF2=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }
    
    while(SB2==0  || checkGameControl(SB2))
    {        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle2();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (press key to remap)");

		DrawLogo(25, 575);

        SB2=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }
    
    while(SL2==0 || checkGameControl(SL2))
    {        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle2();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Left : (press key to remap)");

		DrawLogo(25, 575);

        SL2=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }
    
    while(SR2==0 || checkGameControl(SR2))
    {        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        DrawBackground();
		DrawModeTitle2();
		DrawKeyboardSetting();

		double y=180.0;
		double dy=40.0;
		glColor3ub(155, 155, 155);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Up : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Down : (OK)");
		y+=dy;
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Left : (OK)");
		y+=dy;
		glColor3ub(255, 255, 255);
		glRasterPos2d(100,y);
		YsGlDrawFontBitmap16x20 ("Right : (press key to remap)");

		DrawLogo(25, 575);

        SR2=FsInkey();
        FsSwapBuffers();
        FsSleep(20);
    }    
    
}


void Button::Update()
{
	// Updates stored values of the button object
	FsPollDevice();
	// Intigers such as U and D correspond to up and down buttons being pressed
	// If it is being pressed, it is a 1, otherwise it is a 0
    if(0!=FsGetKeyState(SF))
        F=1;
	else
		F=0;
    if(0!=FsGetKeyState(SB))
        B=1;
	else
		B=0;
	if(0!=FsGetKeyState(SL))
        L=1;
	else
		L=0;
    if(0!=FsGetKeyState(SR))
        R=1;
	else
		R=0;
	if(0!=FsGetKeyState(SU))
        U=1;
	else
		U=0;
	if(0!=FsGetKeyState(SD))
        D=1;
	else
		D=0;
    if(0!=FsGetKeyState(FSKEY_ESC))
        E=1; 
	else
		E=0;    
	if(0!=FsGetKeyState(GR))
        reset =1;
	else
		reset = 0;
	if(0 != FsGetKeyState(GC))
		cont = 1;
	else
		cont = 0;

	if(0 != FsGetKeyState(GP))
	{
		pause = 1;
	}
	else
		pause = 0;

	if(0 != FsGetKeyState(G1))
		one = 1;
	else
		one = 0;

	if(0 != FsGetKeyState(G2))
	{
		two = 1;
	}
	else
		two = 0;


	
}


