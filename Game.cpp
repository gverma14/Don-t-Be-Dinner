#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "stopwatch.h"
#include "boundary.h"
#include "button.h"
#include "camera.h"
#include "hook.h"
#include "menu.h"
#include "obstacle.h"
#include "obstacleHandler.h"
#include "player.h"
#include "track.h"
#include "ending.h"


#include <GL/gl.h>
#include <GL/glu.h>
#include "glm.h"
#include <windows.h>
#include "stdafx.h"


//This code integrates the movement of an individual fish with ability to reset, ESC, and move in the game
//Default Controls - UP = Forward, DOWN = Backward, LEFT = left, RIGHT = right, O-Move Upwards in Y Direction, L - Move Downwards in Y Direction
//K - Tilt up, M - Tilt down
//This class integrates all of the boundaries, hooks, fish, game controls, menus, and time steps in the game
//See README for running of file



class Game
{
public:
	int gamestate;
	int runtime;

	Game();
	~Game();
	void run();
	//temp
	int cameratarget;
	//Statistics endGame();
	int multienabled;
	void endGame();
protected:
	//Player playerList[2];
	Player* playerList;
	const int nPlayers;
	//Obstacle obstacleList;
	int nObstacles;
	//Boundary B;
	Button bm;
	void advanceTimeStep();
	CameraObject c;
	void resetPlayers();
	void drawStuff();
	void drawmodel_fish();
	void DrawHud(const Player &p, int numPlayers);
	const double pie;
	PathPlanning path;
	const int blength;
    Boundary Path;
	Boundary Bound[4];
	int xbound[25];
	int zbound[25];
	void fillArray(int*x, int*z, int blength);
	void drawfishes();
	Stopwatch W;
	ObstacleHandler handler;
	void drawmodel_fish_mod();
	void drawmodel_fish_mod2();
	void StartGame();
	
	
};


void Game::fillArray(int* x, int* z, int blength)
{
	for(int i = 0; i < blength; i++)
	{
		xbound[i] = x[i];
		zbound[i] = z[i];
	}

}


Game::Game():pie(3.14159), blength(25), nPlayers(47)
{
	nObstacles = 0;

	
	resetPlayers();
	cameratarget=0;
	int count=0;			//Counter used in for loops
	int time=0;				//COunter that keeps track of the current time
	const int blength=25;	//Length of the boundary
	int x[blength]={0,0,0,10, 40, 60,40, 20, 0, -10, -50, 0,0,10, 40, 80,40, 60, 65, -10, -50, 0,0,0,0};//Path coordinates
	int z[blength]={0,20,100,120, 150, 180, 240, 300, 360, 420, 480, 550,601, 660, 720, 780, 850,901, 950, 1000, 1080, 1200,1400,1600,1620};
	
	fillArray(x,z, blength);
	
	Path = Boundary(path.centerx, path.centerz, path.plg.nVertex, 'o');//Create the main path
	

	Bound[1] = Boundary(path.leftx, path.leftz, path.plg.nVertex,'l');		//left bound
	Bound[0] = Boundary(path.lleftx, path.lleftz, path.plg.nVertex, 'll');	//Far left bound
	Bound[2] = Boundary(path.rightx, path.rightz, path.plg.nVertex, 'r');		//Right bound
	Bound[3] = Boundary(path.rrightx, path.rrightz, path.plg.nVertex,'rr');	//Far right bound
	
	handler.generateHooks(250, Path, Bound[1], Bound[2]);
	
	StartGame();
}


void Game::StartGame()
{
	Player* P = playerList;
	const int numplayers = 47;
	Boundary BL = Bound[1];
	Boundary BR = Bound[2];


	int playerType [numplayers]={0,0,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

	for(int count=0;count<numplayers;count++)	// Run once for every player
	{
		P[count].Reset();
		P[count].idno  = count;	
		P[count].SetPlayerType(playerType[count]);
		P[count].Place(Path,BL,BR);
	}
	
	
}

Game::~Game()
{
	//delete [] playerList;
}

void Game::resetPlayers()
{
	
	playerList = new Player[nPlayers];
	
}

void Game::run()
{
	int a = Path.x[10];
	gamestate = 1;
	runtime = 0;
	FsOpenWindow(16,16,800,600,1);

	GameMenu menu;
	menu.RunGameMenu2();

	int inmenu = 1;
	
	if(menu.key == FSKEY_ESC)
	{
		gamestate = 0;
	}
	
	switch(menu.key)
	{
	case FSKEY_S:
		//menu.Inputname();

		multienabled = 0;
		playerList[1].SetPlayerType(1);
		menu.RunGameMenu();
		if(menu.key == FSKEY_D)
		{
			bm.Default();
		}
		else if (menu.key == FSKEY_R)
		{
			bm.Remap();
		}
		
		else if(menu.key == FSKEY_ESC)
		{
			gamestate = 0;
		}
		break;
	case FSKEY_M:
		multienabled = 1;
		menu.RunGameMenu();
		if(menu.key == FSKEY_D)
		{
			bm.Default();
			bm.Default2();
		}
		else if(menu.key == FSKEY_R)
		{
			
			bm.Remap();
			bm.Remap2();
		}
		else if(menu.key == FSKEY_ESC)
		{
			gamestate = 0;
		}
		break;
	case FSKEY_ESC:
		gamestate = 0;
		break;
	}

	//printf("%d p1 %d p2\n", bm.SU1, bm.SU2);
	
	bm.Update();
	W.starttimer();
	if(gamestate)
	{
		glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		menu.DrawStart(W.runtime);
		FsSwapBuffers();
		FsSleep(2000);
	}

	while(gamestate)
	{
		if(bm.E)
		{
			gamestate = 0;
		}
		else
		{
			if(bm.pause)
			{
				W.pausetimer();					
			}
			else if(bm.cont && !W.timing)
			{
				W.starttimer();
			}

			if(bm.reset)
			{
				handler.resetAll();
				W.resettimer();
				W.starttimer();
			}

			if(W.timing)
			{
				advanceTimeStep();
				W.updatetimer();				
			}

			

		}
		
		bm.Update();		
	}

	


}



void Game::DrawHud(const Player &P, int numPlayers) //Temp
{
    int wid,hei;
    FsGetWindowSize(wid, hei);
	hei = hei/numPlayers;
    double reference= sqrt(((double)wid*(double)wid+(double)hei*(double)hei));
    glColor3ub(150,150,150);
    glBegin(GL_QUADS);
    glVertex2i((reference/12)+((reference/10)),(reference/100));
    glVertex2i((reference/12)+((reference/10)),((reference/100))+(reference/100));
    glVertex2i((reference/12)+P.Vmin/P.Vmax*((reference/10)),((reference/100))+(reference/100));
    glVertex2i((reference/12)+P.Vmin/P.Vmax*((reference/10)),((reference/100)));
    if(P.Vp>0)
    {
        glColor3ub(0,255,0);
    }
    else
    {
        glColor3ub(255,0,0);
    }
    
   
    glVertex2i((reference/12),(reference/100));
    glVertex2i((reference/12),((reference/100))+(reference/100));
    glVertex2i((reference/12)+P.Vp/P.Vmax*((reference/10)),((reference/100))+(reference/100));
    glVertex2i((reference/12)+P.Vp/P.Vmax*((reference/10)),(reference/100));
    
    glColor3ub(0,0,0);
    glVertex2i((reference/12)+(wid/700),((reference/100)));
    glVertex2i((reference/12)+(wid/700),((reference/100))+(reference/100));
    glVertex2i((reference/12)-(wid/700),((reference/100))+(reference/100));
    glVertex2i((reference/12)-(wid/700),((reference/100)));
    glEnd();
    
    
    int i;
    for(i=0;i<100;i++)
    {
        glColor3ub(150, 225, 0);
        glBegin(GL_QUADS);
        glVertex2d((reference/15)+(reference/30)*cos(3.6*i*pie/180),(reference/15)+(reference/30)*sin(3.6*i*pie/180));
        glVertex2d((reference/15)+(reference/30)*cos(3.6*(i+1)*pie/180),(reference/15)+(reference/30)*sin(3.6*(i+1)*pie/180));
        glVertex2d((reference/15)+(reference*1.2/30)*cos(3.6*(i+1)*pie/180),(reference/15)+(reference*1.2/30)*sin(3.6*(i+1)*pie/180));
        glVertex2d((reference/15)+(reference*1.2/30)*cos(3.6*i*pie/180),(reference/15)+(reference*1.2/30)*sin(3.6*i*pie/180));
        
        glColor3ub(0, 125, 125);
        glBegin(GL_QUADS);
        glVertex2d((reference/15)+(reference/30)*cos(3.6*i*pie/180),(reference/15)+(reference/30)*sin(3.6*i*pie/180));
        glVertex2d((reference/15)+(reference/30)*cos(3.6*(i+1)*pie/180),(reference/15)+(reference/30)*sin(3.6*(i+1)*pie/180));
        glVertex2d((reference/15), (reference/15));
        glVertex2d((reference/15), (reference/15));
        glEnd();
    }
    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d((reference/15), (reference/15)-(reference/30));
    glVertex2d((reference/15), (reference/15)-(reference/30)-(reference/100));
    glVertex2d((reference/15), (reference/15)+(reference/30));
    glVertex2d((reference/15), (reference/15)+(reference/30)+(reference/100));
    glVertex2d((reference/15)+(reference/30), (reference/15));
    glVertex2d((reference/15)+(reference/30)+(reference/100), (reference/15));
    glVertex2d((reference/15)-(reference/30), (reference/15));
    glVertex2d((reference/15)-(reference/30)-(reference/100), (reference/15));
    glEnd();
    
    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i((reference/15)+cos(P.t*pi/180)*(reference/35),(reference/15)+sin(P.t*pi/180)*(reference/35));
    glVertex2i((reference/15)+cos((P.t+135)*pi/180)*(reference/150),(reference/15)+sin((P.t+135)*3.14159/180)*(reference/150));    
    glVertex2i((reference/15)+cos((P.t-135)*pi/180)*(reference/150),(reference/15)+sin((P.t-135)*3.14159/180)*(reference/150));    
    glEnd();
    
    if(P.t>0&&P.t<180&&!P.finish)
    {
        switch(time(NULL)%2)
        {
            case 0:
                int i;
                for(i=0;i<100;i++)
                {
                    glColor3ub(255,0,0);
                    glBegin(GL_TRIANGLES);
                    glVertex2d(wid/2+(reference/45)*cos(3.6*i*pie/180),hei/2+(reference/45)*sin(3.6*i*pie/180));
                    glVertex2d(wid/2+(reference/45)*cos(3.6*(i+1)*pie/180),hei/2+(reference/45)*sin(3.6*(i+1)*pie/180));
                    glVertex2d(wid/2,hei/2);
                    glVertex2d(wid/2,hei/2);
                    glEnd();
                    
                    glColor3ub(255, 255, 255);
                    glBegin(GL_QUADS);
                    glVertex2d((wid/2)+(reference/120), (hei/2)+(reference/350));
                    glVertex2d((wid/2)+(reference/120), (hei/2)-(reference/350));
                    glVertex2d((wid/2)-(reference/120), (hei/2)-(reference/350));
                    glVertex2d((wid/2)-(reference/120), (hei/2)+(reference/350));
                    glEnd();
                    
                }
                break;
            case 1:
                break;
        }
    }
    
    W.Draw();
    
}

void Game::drawStuff()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	int wid,hei;
    FsGetWindowSize(wid,hei);
	
	if(multienabled)
		glViewport(0,hei/2,wid,hei/2);
	else
		glViewport(0,0,wid,hei);

	//glViewport(0,0,wid,hei);

	
	//printf("%d\n", multienabled);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glColor3ub(0,0,255);
	glBegin(GL_QUADS);
	glVertex2d(0,0);
	glVertex2d(wid,0);
	glVertex2d(wid,hei);
	glVertex2d(0,hei);
	glEnd();


    // Set up 3D drawing
	c.Render(playerList[0]);
	c.SetUpCameraProjection(multienabled);
    c.SetUpCameraTransformation();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);

	//Draw Stuff in 3D here
	

	for(int i = 0; i < nPlayers; i++)
	{
		playerList[i].Draw(runtime);
	}
	

	path.Draw();
	handler.draw();
	
	
	//2d drawing
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(multienabled)
		glOrtho(0,(float)wid-1,(float)hei/2-1,0,-1,1);
	else
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);


	DrawHud(playerList[0],multienabled+1);

	//********************SECOND FISH HERE
	if(multienabled)
	{
		FsGetWindowSize(wid,hei);

		glViewport(0,0,wid,hei/2);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3ub(0,0,255);
		glBegin(GL_QUADS);
		glVertex2d(0,0);
		glVertex2d(wid,0);
		glVertex2d(wid,hei);
		glVertex2d(0,hei);
		glEnd();


		// Set up 3D drawing
		c.Render(playerList[1]);
		c.SetUpCameraProjection(multienabled);
		c.SetUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1,1);

		//Draw Stuff in 3D here
		
   		for(int i = 0; i < nPlayers; i++)
		{
			playerList[i].Draw(runtime);
		}
	


		path.Draw();
		handler.draw();
	
	
		//2d drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei/2-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);


		DrawHud(playerList[1],multienabled+1);
	}

	FsSwapBuffers();
}

void Game::advanceTimeStep()
{
	
	Hook* hookArr = handler.getHookArray();


	for(int i = 0; i < nPlayers; i++)
	{
		if(playerList[i].pt == 0)
		{
			if(i == 0)
			{
				bm.Player1Button();
				bm.Update();
			//	printf("%d %d %d %d\r", bm.F, bm.B, bm.L, bm.R);
			}
			else if(i == 1)
			{
				bm.Player2Button();
				bm.Update();
			}
		}
		playerList[i].Go(playerList,nPlayers,Path, Bound[0], Bound[1], Bound[2], Bound[3],bm, hookArr, handler.getArraySize());
		
	}
	
	handler.animate();
	
	drawStuff();
	

	
	int racersfinished = 1;

	for(int i =0; i <nPlayers; i++)
	{
		if(playerList[i].pt == 0 || playerList[i].pt == 1)
		{
			if(!playerList[i].finish)
			{
				racersfinished = 0;
			}
		}
	}

	if(racersfinished)
	{
		W.pausetimer();
		gamestate = 0;
	}
	runtime+=15;

	FsSleep(15);

}

void Game::endGame()
{
	Ending end;
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	end.Initialize();
	//end.DrawHighScore();
	//end.DrawLogo(225, 525);
	int wid, hei;
	
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
	end.DrawCreditList();
	end.DrawLogo(25, 575);
	FsSwapBuffers();

	int terminate=0;
	while (0==terminate)
	{
		FsPollDevice();

		int key=FsInkey();
		switch (key)
		{
        case FSKEY_Q:
            terminate=1;
            break;
		}	

		FsSleep (10);
	}
}

int main(void)
{
	Game g;
	g.run();
	g.endGame();

}
