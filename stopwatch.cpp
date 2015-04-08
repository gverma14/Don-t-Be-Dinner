//Contains functions for maintaining the time throughout the game
//Can start, stop, pause, reset


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "stopwatch.h"

Stopwatch::Stopwatch()
{
    initialize();
}
Stopwatch::~Stopwatch()
{
    cleanup();
    
}
void Stopwatch::cleanup()
{
    timing=NULL;
    runtime=NULL;
    lasttime=NULL;
    milli=NULL;
    sec=NULL;
    min=NULL;
    if(NULL!=tt)
    {
        for(int i=0;i<256;i++)
        {
            tt[i]=NULL;
        }
    }

    
}

void Stopwatch::initialize()
{
   
    timing=0;
    runtime=0;
    lasttime=0;
    milli=0;
    sec=0;
    min=0;
    
    
}

void Stopwatch::resettimer()
{
    cleanup();
    initialize();
    
}

void Stopwatch::starttimer()
{
    timing=1;
    lasttime=clock();
}

void Stopwatch::pausetimer()
{
    timing=0;
    
}
void Stopwatch::updatetimer()
{
    if(timing==1)
    {
        double currenttime=clock();
        runtime+=(currenttime-lasttime);
        lasttime=currenttime;
    }
}


void Stopwatch::Draw()
{
   

    milli=(int)(runtime)%100;
    sec=((int)(runtime) /1000)%60;
    min=((int)(runtime)/60000)%60;
    
    if(NULL!=tt)
    {
        for(int i=0;i<256;i++)
        {
            tt[i]=NULL;
        }
    }
    
    sprintf(tt,"%02d:%02d:%02d",min,sec,milli);

    
    glColor3b(255, 165, 0);
    int wid,hei;
    FsGetWindowSize(wid, hei);
    double reference=sqrt(pow((double)wid, 2)+pow((double)hei, 2));
    glRasterPos2d((wid/2)-(wid/10),(reference/30));
    YsGlDrawFontBitmap20x32(tt);
    
}



/*
int main(void)
{
	
    Stopwatch W;
  
    FsOpenWindow(16,16,800,600,1);
    int key=FSKEY_NULL;
	while(FSKEY_ESC!=key)
    {
		
        FsPollDevice();
        key=FsInkey();
        if ((0!=FsGetKeyState (FSKEY_S))) 
        {
            W.resettimer();
            W.starttimer();
        }
        
        if (0!=FsGetKeyState (FSKEY_P)) 
        {
            W.pausetimer();
        }
        
        if ((0!=FsGetKeyState (FSKEY_R))) 
        {
            W.starttimer();            
        }

        
       
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        W.updatetimer();
        W.Draw();
        
        FsSwapBuffers();
        FsSleep(10);
       
    }*/
